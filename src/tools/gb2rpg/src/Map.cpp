#include "Map.h"

#include "GBFile.h"
#include "Globals.h"

#include "thirdparty/tinyxml2/tinyxml2.h"
#include "src/core/utilities/RPGHelper.h"
#include "src/core/VarMapping.h"
#include "src/core/MemorySizes.h"
#include "src/core/RPGMaker.h"

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstdarg>



// Map-Event Offsets:
// DMG Event has always the first ID.
const static int DMG_EVENT_ID = 1;
// MAP ROM Events start with 2nd ID.
const static int MAP_ROM_ID = 2;

// public
Map::Map(GBFile& gbFile)
    : mapDoc(nullptr) {
    int numOfMapROMs = ((gbFile.getRomSize() * 1024) / (MEMORYSIZES::MAX_PAGES_PER_EVENT * MEMORYSIZES::BYTES_PER_EPAGE)) + 1;
    mapRAMID = MAP_ROM_ID + numOfMapROMs;

    mapDoc = new tinyxml2::XMLDocument(TEMPLATES::MAP);

    generateDMGROM();
    generateMapROM(gbFile, numOfMapROMs);
    generateMapRAM();
}

Map::~Map() {
    if(mapDoc) {
        delete mapDoc;
        mapDoc = nullptr;
    }
}

int Map::genMapFiles(std::vector<GBFile>& gbFiles) {
    for(int i = 0; i < gbFiles.size(); ++i) {
        Map map = Map(gbFiles.at(i));
        
        std::string filePath = EXPORTS::MAP_BASE + generateID(i + 1) + EXPORTS::MAP_TYPE;
        map.mapDoc->SaveFile(filePath.c_str(), true);
    }

    return gbFiles.size();
}


// private
void Map::generateDMGROM() {
    tinyxml2::XMLDocument event(TEMPLATES::EVENT);
    tinyxml2::XMLDocument eventPage(TEMPLATES::EVENT_PAGE);
    tinyxml2::XMLDocument DMGROM(TEMPLATES::DMG_ROM);
    

    // Add DMGROM into event-page
    DMGROM.DeepCloneInsertBackSiblings(&eventPage, eventPage.TraverseElement("//event_commands"));

    // Set Event Page ID
    eventPage.RootElement()->SetAttribute("id", generateID(1).c_str());

    // Insert event-page into event.
    eventPage.DeepCloneInsertBack(&event, event.TraverseElement("//pages"));

    // Set Event ID, Name and Coordinate
    std::string name = "DMGROM";
    setEventIDNameCoord(&event, DMG_EVENT_ID, name, 0, 0);

    // Insert DMG Event into map
    event.DeepCloneInsertBack(mapDoc, mapDoc->TraverseElement("/LMU//events"));
}

void Map::generateMapROM(GBFile& gbFile, int numOfMapROMs) {
    // create all necessary ROM Events
    for(int eventID = MAP_ROM_ID; eventID < MAP_ROM_ID + numOfMapROMs; ++eventID) {
        tinyxml2::XMLDocument event(TEMPLATES::EVENT);
        // creating all necessary event pages.
        for (int pageID = 1; pageID <= MEMORYSIZES::MAX_PAGES_PER_EVENT; ++pageID) {
            if(gbFile.bytesRemaining() <= 0) {
                // The last event-page had all Bytes we needed
                break;
            }

            tinyxml2::XMLDocument eventPage(TEMPLATES::EVENT_PAGE);
            int numLabels = calcNumOfLabels(gbFile);
            bool lastEventPage = isLastEventPage(gbFile);

    
            // 1st: Fill event-page with map-rom-header commands
            tinyxml2::XMLDocument mapRomHeader(TEMPLATES::MAP_ROM_HEADER);
            setupMapRomHeader(&mapRomHeader, numLabels);
            mapRomHeader.DeepCloneInsertBackSiblings(&eventPage, eventPage.TraverseElement("//event_commands"));

            // 2nd: Fill event-page with map-rom-label commands
            for(int labelID = 1; labelID < (numLabels + 1); ++labelID) {
                tinyxml2::XMLDocument mapRomLabel(TEMPLATES::MAP_ROM_LABEL);

                int firstVar = packVariable(gbFile.getBytes(MEMORYSIZES::BYTES_PER_VAR));
                int secondVar = packVariable(gbFile.peekBytes(MEMORYSIZES::BYTES_PER_VAR));
                if(lastEventPage && labelID == numLabels) {
                    // Second variable should indicate garbage value, as it contains data after the GBFile. 
                    secondVar = -9999999;
                }
                setupMapRomLabel(&mapRomLabel, labelID, numLabels, firstVar, secondVar);
                mapRomLabel.DeepCloneInsertBackSiblings(&eventPage, eventPage.TraverseElement("//event_commands"));
            }

            // 3rd: Set Event Page ID
            eventPage.RootElement()->SetAttribute("id", generateID(pageID).c_str());

            // 5th: Insert event-page into event
            eventPage.DeepCloneInsertBack(&event, event.TraverseElement("//pages"));
        }

        // Set Event ID, Name and Coordinate
        std::string name = std::string("ROM") + generateID(eventID - MAP_ROM_ID + 1);
        int xCoord = (eventID - 1) % RPGMAKER::MAP_SIZE_X;
        int yCoord = (eventID - 1) / RPGMAKER::MAP_SIZE_Y;
        setEventIDNameCoord(&event, eventID, name, xCoord, yCoord);

        // Insert event into map
        event.DeepCloneInsertBack(mapDoc, mapDoc->TraverseElement("/LMU//events"));
    }
}

void Map::generateMapRAM() {
    tinyxml2::XMLDocument event(TEMPLATES::EVENT);
    tinyxml2::XMLDocument eventPage(TEMPLATES::EVENT_PAGE);

    // insert event-page into event.
    eventPage.DeepCloneInsertBack(&event, event.TraverseElement("//pages"));

    for (int i = 0; i < MEMORYSIZES::NUM_DMG_RAM_EVENTS; ++i) {

        // Set Event ID, Name and Coordinate
        std::string name = std::string("RAM") + generateID(i + 1);
        int eventID = mapRAMID + i;
        int xCoord = (eventID - 1) % RPGMAKER::MAP_SIZE_X;
        int yCoord = (eventID - 1) / RPGMAKER::MAP_SIZE_Y;
        setEventIDNameCoord(&event, eventID, name, xCoord, yCoord);

        // Insert event into map
        event.DeepCloneInsertBack(mapDoc, mapDoc->TraverseElement("/LMU//events"));
    }
}

// TODO: This should exist in a different general project.
void Map::setEventIDNameCoord(tinyxml2::XMLDocument* event, int id, std::string& name, int x, int y) {
    assert(x >= 0 && x < RPGMAKER::MAP_SIZE_X);
    assert(y >= 0 && y < RPGMAKER::MAP_SIZE_Y);

    // Set Event ID
    event->RootElement()->SetAttribute("id", generateID(id).c_str());

    // Set Event Name
    auto* nameElem = event->TraverseElement("//name")->FirstChild();
    nameElem->SetValue((name).c_str());

    // Set Event Coordinates
    auto* xCoord = event->TraverseElement("//x")->FirstChild();
    xCoord->SetValue(std::to_string((id - 1) % RPGMAKER::MAP_SIZE_X).c_str());

    auto* yCoord = event->TraverseElement("//y")->FirstChild();
    yCoord->SetValue(std::to_string((id - 1) / RPGMAKER::MAP_SIZE_Y).c_str());
}

// TODO: This should exist in a different general project. And have wrapper functions around them (with fixed variable size) that allow named parameters which makes this problem easier. And to not have magic numbers I need enums/typedeffs for each command type!
void setCommandParameters(tinyxml2::XMLNode* command, int numParam, ...) {
    va_list args;
    std::stringstream sstr;
    va_start(args, numParam);
    for(int i = 0; i < numParam; ++i ) {
        sstr << va_arg(args, int);
        if(i < (numParam - 1)) {
            sstr << " ";
        } 
    }
    va_end(args);

    auto* parameters = command->TraverseElement("/parameters")->FirstChild()->ToText();
    parameters->SetValue(sstr.str().c_str());
}

void setCommandType(tinyxml2::XMLNode* command, int newType) {
    auto* code = command->FirstChildElement("code")->FirstChild();
    code->SetValue(std::to_string(newType).c_str());
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

void Map::setupMapRomHeader(tinyxml2::XMLDocument* mapRomHeader, int numLabels) {
    // Need to change the boilerplate code (see map_rom_header.xml for details).
    // ByteOffset = (ByteOffset / BYTES_PER_VAR):
    auto* command = mapRomHeader->RootElement()->TraverseElement("./EventCommand");
    setCommandParameters(command, 7, 0, VARMAPPING::BYTE_OFFSET_ID, VARMAPPING::BYTE_OFFSET_ID, 4, 0, MEMORYSIZES::BYTES_PER_VAR, 0);

    // LabelID = ByteOffset
    command = command->TraverseElement("./EventCommand");
    setCommandParameters(command, 7, 0, VARMAPPING::LABEL_ID, VARMAPPING::LABEL_ID, 0, 1, VARMAPPING::BYTE_OFFSET_ID, 0);

    // LabelID += 1:
    command = command->TraverseElement("./EventCommand");
    setCommandParameters(command, 7, 0, VARMAPPING::LABEL_ID, VARMAPPING::LABEL_ID, 1, 0, 1, 0);

    // JumpToLabel numLabels / 2
    command = command->TraverseElement("./EventCommand");
    setCommandParameters(command, 1, numLabels / 2);
}

void Map::setupMapRomLabel(tinyxml2::XMLDocument* mapRomLabel, int labelID, int numLabels, int firstVar, int secondVar) {
    // Need to change the boilerplate code (see map_rom_label.xml for details).
    // Label X
    auto* command = mapRomLabel->RootElement();
    setCommandParameters(command, 1, labelID);

    // IF(LabelID < X)
    command = command->TraverseElement("./EventCommand");
    setCommandParameters(command, 6, 1, VARMAPPING::LABEL_ID, 0, labelID, 4, 0);
    
    // JumpToLabel X - (min(X, 1.000 - X) / 2)
    command = command->TraverseElement("./EventCommand");
    float minDistance = std::min(labelID, numLabels - labelID);
    if(labelID == 1) {
        // The first MapRomLabel does not need to jump here, instead change the command to EndEventProcessing
        setCommandType(command, 12310);
        setCommandParameters(command, 0);
    } else {
        int newID = labelID - ceil(minDistance/2.0f);
        setCommandParameters(command, 1, newID);
    }

    // IF(LabelID > X)
    command = command->TraverseElement("./EventCommand./EventCommand./EventCommand");
    setCommandParameters(command, 6, 1, VARMAPPING::LABEL_ID, 0, labelID, 3, 0);

    // JumpToLabel X + (min(X, 1.000 - X) / 2)
    command = command->TraverseElement("./EventCommand");
    if(labelID == numLabels) {
        // The last MapRomLabel does not need to jump here, instead change the command to EndEventProcessing.
        setCommandType(command, 12310);
        setCommandParameters(command, 0);
    } else {
        int newID = labelID + ceil(minDistance/2.0f);
        setCommandParameters(command, 1, newID);
    }

    // READVAR1 = LABELXVALUE1
    command = command->TraverseElement("./EventCommand./EventCommand./EventCommand");
    setCommandParameters(command, 7, 0, VARMAPPING::READ_VAR_1, VARMAPPING::READ_VAR_1, 0, 0, firstVar, 0);

    // READVAR2 = LABELXVALUE2
    command = command->TraverseElement("./EventCommand");
    setCommandParameters(command, 7, 0, VARMAPPING::READ_VAR_2, VARMAPPING::READ_VAR_2, 0, 0, secondVar, 0);
}