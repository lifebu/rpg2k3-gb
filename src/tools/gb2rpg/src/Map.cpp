#include "Map.h"

#include "GBFile.h"
#include "Globals.h"

#include "core/lcf/event/EventCommandFactory.h"
#include "core/lcf/Map.h"
#include "core/lcf_serializers/MapSerializer.h"
#include "core/lcf_serializers/common/EventCommandSerializer.h"

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
void Map::genMapFiles(std::vector<GBFile>& gbFiles) {
    std::cout << "Generating Map Files.\n";
    for(int i = 0; i < gbFiles.size(); ++i) {
        auto& gbFile = gbFiles.at(i);
        int numOfMapROMs = ((gbFile.getRomSize() * 1024) / (RPGMAKER::MAX_PAGES_PER_EVENT * MEMORYSIZES::BYTES_PER_EPAGE)) + 1;

        std::string fileName = EXPORTS::MAP_FILE_BASE + generateID(i + 1) + EXPORTS::MAP_FILE_TYPE;
        std::string filePath = PROJECT::PROJECT_DIR + fileName;
        std::cout << "Generating Map: " << fileName << "\n";

        lcf::Map map(1 + numOfMapROMs + MEMORYSIZES::NUM_DMG_RAM_EVENTS);

        generateDMGROM(map);
        generateMapROM(map, gbFile, numOfMapROMs);
        generateMapRAM(map);

        lcf::MapSerializer().ToFile(filePath, map);
    }
}

// private
void Map::generateDMGROM(lcf::Map& map) {
    lcf::Event& event = map.addEvent("DMGROM", 0, 0);
    lcf::EventPage& eventPage = event.addEventPage();

    std::vector<lcf::EventCommand> DMGCommands = lcf::EventCommandSerializer().MultipleFromFile(TEMPLATES::DMG_ROM);
    eventPage.addEventCommands(DMGCommands);
}

void Map::generateMapROM(lcf::Map& map, GBFile& gbFile, int numOfMapROMs) {
    // pre-load data
    std::vector<lcf::EventCommand> mapRomHeader = lcf::EventCommandSerializer().MultipleFromFile(TEMPLATES::MAP_ROM_HEADER);
    std::vector<lcf::EventCommand> mapRomLabel = lcf::EventCommandSerializer().MultipleFromFile(TEMPLATES::MAP_ROM_LABEL);
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
            setupMapRomHeader(mapRomHeader, numLabels);
            eventPage.addEventCommands(mapRomHeader);

            // Fill event-page with map-rom-label commands
            for (int labelID = 1; labelID <= numLabels; ++labelID) {
                int firstVar = packVariable(gbFile.getBytes(MEMORYSIZES::BYTES_PER_VAR));
                int secondVar = packVariable(gbFile.peekBytes(MEMORYSIZES::BYTES_PER_VAR));
                if(lastEventPage && labelID == numLabels) {
                    // Second variable should indicate garbage value, as it contains data after the GBFile. 
                    secondVar = -9999999;
                }

                setupMapRomLabel(mapRomLabel, labelID, numLabels, firstVar, secondVar);
                eventPage.addEventCommands(mapRomLabel);
            }
        }
    }
}

void Map::generateMapRAM(lcf::Map& map) {
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
int Map::calcNumOfLabels(GBFile& gbFile) {
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

bool Map::isLastEventPage(GBFile& gbFile) {
    bool isLastEventPage = false;
    if (gbFile.bytesRemaining() <= MEMORYSIZES::VARS_PER_EPAGE * MEMORYSIZES::BYTES_PER_VAR) {
        isLastEventPage = true;
    }
    return isLastEventPage;
}

void Map::setupMapRomHeader(std::vector<lcf::EventCommand>& mapRomHeader, int numLabels) {
    assert(mapRomHeader.size() == 6);

    // Need to change the boilerplate code (see map_rom_header.xml for details).
    // Comment
    lcf::EventCommandFactory::GenFirstLineComment(mapRomHeader.at(0), "Convert Offset from Bytes to Variables");

    // ByteOffset = (ByteOffset / BYTES_PER_VAR):
    lcf::EventCommandFactory::GenControlVariable(
        mapRomHeader.at(1), 
        lcf::ControlVariableCommand::Type::SINGLE_VARIABLE,
        VARMAPPING::BYTE_OFFSET_ID, VARMAPPING::BYTE_OFFSET_ID,
        lcf::ControlVariableCommand::Operation::OPERATION_DIV,
        lcf::ControlVariableCommand::OperandTypes::OPERANDS_CONSTANT,
        MEMORYSIZES::BYTES_PER_VAR, 0);
    
    // LabelID = ByteOffset
    lcf::EventCommandFactory::GenControlVariable(
        mapRomHeader.at(2), 
        lcf::ControlVariableCommand::Type::SINGLE_VARIABLE,
        VARMAPPING::LABEL_ID, VARMAPPING::LABEL_ID,
        lcf::ControlVariableCommand::Operation::OPERATION_SET,
        lcf::ControlVariableCommand::OperandTypes::OPERANDS_VARIABLE,
        VARMAPPING::BYTE_OFFSET_ID, 0);

    // LabelID += 1
    lcf::EventCommandFactory::GenControlVariable(
        mapRomHeader.at(3), 
        lcf::ControlVariableCommand::Type::SINGLE_VARIABLE,
        VARMAPPING::LABEL_ID, VARMAPPING::LABEL_ID,
        lcf::ControlVariableCommand::Operation::OPERATION_ADD,
        lcf::ControlVariableCommand::OperandTypes::OPERANDS_CONSTANT,
        1, 0);

    // JumpToLabel numLabels / 2
    lcf::EventCommandFactory::GenJumpToLabel(mapRomHeader.at(4), numLabels / 2);
}

void Map::setupMapRomLabel(std::vector<lcf::EventCommand>& mapRomLabel, int labelID, int numLabels, int firstVar, int secondVar) {
    assert(mapRomLabel.size() == 11);

    // Need to change the boilerplate code (see map_rom_label.xml for details).
    // Label X
    lcf::EventCommandFactory::GenLabel(mapRomLabel.at(0), labelID);

    // IF(LabelID < X)
    lcf::EventCommandFactory::GenConditionalBranch(
        mapRomLabel.at(1), 
        lcf::ConditionalBranchCommand::Type::VARIABLE,
        VARMAPPING::LABEL_ID, 
        lcf::ConditionalBranchCommand::RHSType::USE_CONSTANT, labelID, 
        lcf::ConditionalBranchCommand::Comparison::LESS, false);
    
    // JumpToLabel X - (min(X, 1.000 - X) / 2)
    float minDistance = std::min(labelID, numLabels - labelID);
    if(labelID == 1) 
    {
        // The first MapRomLabel does not need to jump here, instead change the command to EndEventProcessing
        lcf::EventCommandFactory::GenEndEventProcessing(mapRomLabel.at(2));
    }
    else 
    {
        int newID = labelID - ceil(minDistance/2.0f);
        lcf::EventCommandFactory::GenJumpToLabel(mapRomLabel.at(2), newID);
    }

    // NOOP
    lcf::EventCommandFactory::GenNoOp(mapRomLabel.at(3));

    // ENDIF
    lcf::EventCommandFactory::GenEndBranch(mapRomLabel.at(4));

    // IF(LabelID > X)
    lcf::EventCommandFactory::GenConditionalBranch(
        mapRomLabel.at(5), 
        lcf::ConditionalBranchCommand::Type::VARIABLE,
        VARMAPPING::LABEL_ID, 
        lcf::ConditionalBranchCommand::RHSType::USE_CONSTANT, labelID, 
        lcf::ConditionalBranchCommand::Comparison::GREATER, false);

    // JumpToLabel X + (min(X, 1.000 - X) / 2)
    if(labelID == numLabels) 
    {
        // The last MapRomLabel does not need to jump here, instead change the command to EndEventProcessing.
        lcf::EventCommandFactory::GenEndEventProcessing(mapRomLabel.at(6));
    } 
    else 
    {
        int newID = labelID + ceil(minDistance/2.0f);
        lcf::EventCommandFactory::GenJumpToLabel(mapRomLabel.at(6), newID);
    }

    // NOOP
    lcf::EventCommandFactory::GenNoOp(mapRomLabel.at(7));

    // ENDIF
    lcf::EventCommandFactory::GenEndBranch(mapRomLabel.at(8));

    // READVAR1 = LABELXVALUE1
    lcf::EventCommandFactory::GenControlVariable(
        mapRomLabel.at(9), 
        lcf::ControlVariableCommand::Type::SINGLE_VARIABLE,
        VARMAPPING::READ_VAR_1, VARMAPPING::READ_VAR_1,
        lcf::ControlVariableCommand::Operation::OPERATION_SET,
        lcf::ControlVariableCommand::OperandTypes::OPERANDS_CONSTANT,
        firstVar, 0);

    // READVAR2 = LABELXVALUE2
    lcf::EventCommandFactory::GenControlVariable(
        mapRomLabel.at(9), 
        lcf::ControlVariableCommand::Type::SINGLE_VARIABLE,
        VARMAPPING::READ_VAR_2, VARMAPPING::READ_VAR_2,
        lcf::ControlVariableCommand::Operation::OPERATION_SET,
        lcf::ControlVariableCommand::OperandTypes::OPERANDS_CONSTANT,
        secondVar, 0);
}