#include "Map.h"

#include "GBFile.h"
#include "Globals.h"

#include "core/def/Globals.h"
#include "core/lcf/event/EventCommandFactory.h"
#include "core/lcf/Map.h"
#include "core/lcf_serializers/MapSerializer.h"
#include "core/lcf_serializers/MapSerializerRAPID.h"
#include "core/lcf_serializers/EventCommandSerializer.h"

#include <iostream>
#include <cassert>
#include <cmath>

using namespace gb2rpg;

// Map-Event Offsets:
// DMG Event has always the first ID.
const static int DMG_EVENT_ID = 1;
// MAP ROM Events start with 2nd ID.
const static int MAP_ROM_ID = 2;

// public
void Map::genMapFiles(std::vector<GBFile>& gbFiles, CLIOptions::XMLParser parserToUse) 
{
    std::cout << "Generating Map Files.\n";
    for(int i = 0; i < gbFiles.size(); ++i) 
    {
        auto& gbFile = gbFiles.at(i);
        int numOfMapROMs = ((gbFile.getRomSize() * 1024) / (RPGMAKER::MAX_PAGES_PER_EVENT * MEMORYSIZES::BYTES_PER_EPAGE)) + 1;

        std::string fileName = GLOBALS::EXPORTS::MAP_FILE_BASE + generateID(i + 1) + GLOBALS::EXPORTS::MAP_FILE_TYPE;
        std::string filePath = GLOBALS::PROJECT::PROJECT_DIR + fileName;
        std::cout << "Generating Map: " << fileName << "\n";

        lcf::Map map(1 + numOfMapROMs + MEMORYSIZES::NUM_DMG_RAM_EVENTS);

        generateDMGROM(map);
        generateMapROM(map, gbFile, numOfMapROMs);
        generateMapRAM(map);

        if(parserToUse == CLIOptions::XMLParser::TINYXML)
        {
            lcf::MapSerializer::ToFile(filePath, map);
        }
        else if (parserToUse == CLIOptions::XMLParser::RAPIDXML)
        {
            lcf::MapSerializerRAPID::ToFile(filePath, map);
        }
    }
}

// private
void Map::generateDMGROM(lcf::Map& map) 
{
    lcf::Event& event = map.addEvent("DMGROM", 0, 0);
    lcf::EventPage& eventPage = event.addEventPage();

    std::vector<lcf::EventCommand> DMGCommands = lcf::EventCommandSerializer::MultipleFromFile(TEMPLATES::DMG_ROM);
    eventPage.addEventCommands(DMGCommands);
}

void Map::generateMapROM(lcf::Map& map, GBFile& gbFile, int numOfMapROMs) 
{
    int startingID = map.nextEventID();

    // create all necessary ROM Events
    for(int i = 0; i < numOfMapROMs; ++i) {        
        std::string name = std::string("ROM") + generateID(map.nextEventID() - startingID + 1);
        int x = (map.nextEventID() - 1) % RPGMAKER::MAP_SIZE_X;
        int y = (map.nextEventID() - 1) / RPGMAKER::MAP_SIZE_Y;

        lcf::Event& event = map.addEvent(name, x, y);

        // creating all necessary event pages.
        for (int j = 0; j < RPGMAKER::MAX_PAGES_PER_EVENT; ++j) {
            // The last event-page had all Bytes we needed
            if(gbFile.bytesRemaining() <= 0) break;

            lcf::EventPage& eventPage = event.addEventPage();
            int numLabels = calcNumOfLabels(gbFile);
            bool lastEventPage = isLastEventPage(gbFile);

            // Fill event-page with map-rom-header commands
            std::vector<lcf::EventCommand> mapRomHeader = setupMapRomHeader(numLabels);
            eventPage.addEventCommands(mapRomHeader);

            // Fill event-page with map-rom-label commands
            for (int labelID = 1; labelID <= numLabels; ++labelID) {
                int firstVar = packVariable(gbFile.getBytes(MEMORYSIZES::BYTES_PER_VAR));
                int secondVar = packVariable(gbFile.peekBytes(MEMORYSIZES::BYTES_PER_VAR));
                if(lastEventPage && labelID == numLabels) {
                    // Second variable should indicate garbage value, as it contains data after the GBFile. 
                    secondVar = -9999999;
                }

                std::vector<lcf::EventCommand> mapRomLabel = setupMapRomLabel(labelID, numLabels, firstVar, secondVar);
                eventPage.addEventCommands(mapRomLabel);
            }
        }
    }
}

void Map::generateMapRAM(lcf::Map& map) 
{
    int startingID = map.nextEventID();
    for (int i = 0; i < MEMORYSIZES::NUM_DMG_RAM_EVENTS; ++i) {
        std::string name = std::string("RAM") + generateID(map.nextEventID() - startingID + 1);
        int x = (map.nextEventID() - 1) % RPGMAKER::MAP_SIZE_X;
        int y = (map.nextEventID() - 1) / RPGMAKER::MAP_SIZE_Y;

        lcf::Event& event = map.addEvent(name, x, y);
        lcf::EventPage& eventPage = event.addEventPage();
    }
}


// Helper functions
int Map::calcNumOfLabels(GBFile& gbFile) 
{
    bool isLastEventPage = false;
    int numLabels = MEMORYSIZES::VARS_PER_EPAGE;
    if (gbFile.bytesRemaining() == MEMORYSIZES::VARS_PER_EPAGE * MEMORYSIZES::BYTES_PER_VAR) {
        isLastEventPage = true;
    }
    else if(gbFile.bytesRemaining() < MEMORYSIZES::VARS_PER_EPAGE * MEMORYSIZES::BYTES_PER_VAR) {
        // This is the last event-page
        isLastEventPage = true;
        numLabels = ceil((float)gbFile.bytesRemaining() / (float)MEMORYSIZES::BYTES_PER_VAR);
    }
    return numLabels;
}

bool Map::isLastEventPage(GBFile& gbFile) 
{
    bool isLastEventPage = false;
    if (gbFile.bytesRemaining() <= MEMORYSIZES::VARS_PER_EPAGE * MEMORYSIZES::BYTES_PER_VAR) {
        isLastEventPage = true;
    }
    return isLastEventPage;
}

std::vector<lcf::EventCommand> Map::setupMapRomHeader(int numLabels) 
{
    std::vector<lcf::EventCommand> mapRomHeader;

    // Comment
    //mapRomHeader.push_back(lcf::EventCommandFactory::GenFirstLineComment("Convert Offset from Bytes to Variables"));

    // ByteOffset = (ByteOffset / BYTES_PER_VAR):
    mapRomHeader.push_back(lcf::EventCommandFactory::GenControlVariable(
        lcf::ControlVariable::Type::SINGLE_VARIABLE,
        VARMAPPING::BYTE_OFFSET_ID, VARMAPPING::BYTE_OFFSET_ID,
        lcf::ControlVariable::Operation::OPERATION_DIV,
        lcf::ControlVariable::OperandTypes::OPERANDS_CONSTANT,
        MEMORYSIZES::BYTES_PER_VAR, 0));
    
    // LabelID = ByteOffset
    mapRomHeader.push_back(lcf::EventCommandFactory::GenControlVariable(
        lcf::ControlVariable::Type::SINGLE_VARIABLE,
        VARMAPPING::LABEL_ID, VARMAPPING::LABEL_ID,
        lcf::ControlVariable::Operation::OPERATION_SET,
        lcf::ControlVariable::OperandTypes::OPERANDS_VARIABLE,
        VARMAPPING::BYTE_OFFSET_ID, 0));

    // LabelID += 1
    mapRomHeader.push_back(lcf::EventCommandFactory::GenControlVariable(
        lcf::ControlVariable::Type::SINGLE_VARIABLE,
        VARMAPPING::LABEL_ID, VARMAPPING::LABEL_ID,
        lcf::ControlVariable::Operation::OPERATION_ADD,
        lcf::ControlVariable::OperandTypes::OPERANDS_CONSTANT,
        1, 0));

    // JumpToLabel numLabels / 2
    mapRomHeader.push_back(lcf::EventCommandFactory::GenJumpToLabel(numLabels / 2));

    // Empty comment
    //mapRomHeader.push_back(lcf::EventCommandFactory::GenFirstLineComment(""));

    assert(mapRomHeader.size() == MEMORYSIZES::MAP_ROM_HEADER_COUNT);
    return mapRomHeader;
}

std::vector<lcf::EventCommand> Map::setupMapRomLabel(int labelID, int numLabels, int firstVar, int secondVar) 
{
    std::vector<lcf::EventCommand> mapRomLabel;

    // Label X
    mapRomLabel.push_back(lcf::EventCommandFactory::GenLabel(labelID));

    // IF(LabelID < X)
    mapRomLabel.push_back(lcf::EventCommandFactory::GenConditionalBranch(
        lcf::ConditionalBranch::Type::VARIABLE,
        VARMAPPING::LABEL_ID, 
        lcf::ConditionalBranch::RHSType::USE_CONSTANT, labelID, 
        lcf::ConditionalBranch::Comparison::LESS, false));
    
    // JumpToLabel X - (min(X, 1.000 - X) / 2)
    float minDistance = std::min(labelID, numLabels - labelID);
    if(labelID == 1) 
    {
        // The first MapRomLabel does not need to jump here, instead change the command to EndEventProcessing
        mapRomLabel.push_back(lcf::EventCommandFactory::GenEndEventProcessing());
    }
    else 
    {
        int newID = labelID - ceil(minDistance/2.0f);
        mapRomLabel.push_back(lcf::EventCommandFactory::GenJumpToLabel(newID));
    }

    // NOOP
    //mapRomLabel.push_back(lcf::EventCommandFactory::GenNoOp());

    // ENDIF
    mapRomLabel.push_back(lcf::EventCommandFactory::GenEndBranch());

    // IF(LabelID > X)
    mapRomLabel.push_back(lcf::EventCommandFactory::GenConditionalBranch(
        lcf::ConditionalBranch::Type::VARIABLE,
        VARMAPPING::LABEL_ID, 
        lcf::ConditionalBranch::RHSType::USE_CONSTANT, labelID, 
        lcf::ConditionalBranch::Comparison::GREATER, false));

    // JumpToLabel X + (min(X, 1.000 - X) / 2)
    if(labelID == numLabels) 
    {
        // The last MapRomLabel does not need to jump here, instead change the command to EndEventProcessing.
        mapRomLabel.push_back(lcf::EventCommandFactory::GenEndEventProcessing());
    } 
    else 
    {
        int newID = labelID + ceil(minDistance/2.0f);
        mapRomLabel.push_back(lcf::EventCommandFactory::GenJumpToLabel(newID));
    }

    // NOOP
    //mapRomLabel.push_back(lcf::EventCommandFactory::GenNoOp());

    // ENDIF
    mapRomLabel.push_back(lcf::EventCommandFactory::GenEndBranch());

    // READVAR1 = LABELXVALUE1
    mapRomLabel.push_back(lcf::EventCommandFactory::GenControlVariable(
        lcf::ControlVariable::Type::SINGLE_VARIABLE,
        VARMAPPING::READ_VAR_1, VARMAPPING::READ_VAR_1,
        lcf::ControlVariable::Operation::OPERATION_SET,
        lcf::ControlVariable::OperandTypes::OPERANDS_CONSTANT,
        firstVar, 0));

    // READVAR2 = LABELXVALUE2
    mapRomLabel.push_back(lcf::EventCommandFactory::GenControlVariable(
        lcf::ControlVariable::Type::SINGLE_VARIABLE,
        VARMAPPING::READ_VAR_2, VARMAPPING::READ_VAR_2,
        lcf::ControlVariable::Operation::OPERATION_SET,
        lcf::ControlVariable::OperandTypes::OPERANDS_CONSTANT,
        secondVar, 0));
    
    // End Event Processing
    mapRomLabel.push_back(lcf::EventCommandFactory::GenEndEventProcessing());

    assert(mapRomLabel.size() == MEMORYSIZES::MAP_ROM_LABEL_COUNT);
    return mapRomLabel;
}