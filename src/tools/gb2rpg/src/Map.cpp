#include "Map.h"

#include "GBFile.h"
#include "Globals.h"

#include "thirdparty/tinyxml2/tinyxml2.h"
#include "tinyxml2_helper.h"
#include "RPGHelper.h"

#include <iostream>
#include <sstream>
#include <cstdio>
#include <cassert>
#include <cmath>

using namespace std;

// public
Map::Map(GBFile& gbFile)
    : mapDoc(nullptr) {
    int numOfMapROMs = ((gbFile.getRomSize() * 1024) / (MEMORYSIZE::MAX_PAGES_PER_EVENT * MEMORYSIZE::BYTES_PER_EPAGE)) + 1;
    mapRAMID = MEMORYSIZE::MAP_ROM_ID + numOfMapROMs;

    mapDoc = new tinyxml2::XMLDocument;
    mapDoc->LoadFile((FOLDERS::TEMPLATE_PATH + "map/map.xml").c_str());

    generateDMGROM();
    generateMapROM(gbFile);
    generateMapRAM();
}

Map::~Map() {
    if(mapDoc) {
        delete mapDoc;
        mapDoc = nullptr;
    }
}

void Map::exportXML(std::string filePath) {
    mapDoc->SaveFile(filePath.c_str());
}

std::vector<Map> Map::genMapFiles(std::vector<GBFile>& gbFiles) {
    std::vector<Map> maps;
    maps.reserve(gbFiles.size());
    for(auto& gb : gbFiles) {
        maps.emplace_back(gb);
    }
    return maps;
}


// private
void Map::generateDMGROM() {
    // DMGROM does not need to change EventID, PageID, or Position (0,0)
    tinyxml2::XMLDocument event;
    event.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event.xml").c_str());

    tinyxml2::XMLDocument eventPage;
    eventPage.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event_page.xml").c_str());

    tinyxml2::XMLDocument DMGROM;
    DMGROM.LoadFile((FOLDERS::TEMPLATE_PATH + "dmg_rom.xml").c_str());
    

    // Add DMGROM into event-page
    DeepCloneInsertBackAllSiblings(DMGROM.RootElement(), &eventPage,
        eventPage.RootElement()->FirstChildElement("event_commands"));

    // Insert event-page into event.
    DeepCloneInsertBack(eventPage.RootElement(), &event, 
        event.RootElement()->FirstChildElement("pages"));


    // Set Event ID, Name and Coordinate
    std::string name = "DMGROM";
    setEventIDNameCoord(&event, 1, name, 0, 0);

    // Insert DMG Event into map
    DeepCloneInsertBack(event.RootElement(), mapDoc, 
        mapDoc->FirstChildElement("LMU")->FirstChildElement()->FirstChildElement("events"));
}

void Map::generateMapROM(GBFile& gbFile) {
    int numOfMapROMs = ((gbFile.getRomSize() * 1024) / (MEMORYSIZE::MAX_PAGES_PER_EVENT * MEMORYSIZE::BYTES_PER_EPAGE)) + 1;

    // create all necessary ROM Events
    for(int eventID = MEMORYSIZE::MAP_ROM_ID; eventID < MEMORYSIZE::MAP_ROM_ID + numOfMapROMs; ++eventID) {
        tinyxml2::XMLDocument event;
        event.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event.xml").c_str());

        for (int pageID = 1; pageID <= MEMORYSIZE::MAX_PAGES_PER_EVENT; ++pageID) {
            if(gbFile.bytesRemaining() <= 0) {
                // The last event-page had all Bytes we needed
                break;
            }

            // How many Labels does this page need?
            int numLabels;
            if(gbFile.bytesRemaining() >= MEMORYSIZE::VARS_PER_EPAGE * MEMORYSIZE::BYTES_PER_VAR) {
                numLabels = MEMORYSIZE::VARS_PER_EPAGE;
            } else {
                // This is the last event-page
                numLabels = gbFile.bytesRemaining() / MEMORYSIZE::BYTES_PER_VAR;
            }

            // Load event-page
            tinyxml2::XMLDocument eventPage;
            eventPage.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event_page.xml").c_str());

            // Fill event-page with map-rom-header commands
            tinyxml2::XMLDocument mapRomHeader;
            mapRomHeader.LoadFile((FOLDERS::TEMPLATE_PATH + "map_rom_header.xml").c_str());
            setupMapRomHeader(&mapRomHeader, numLabels);

            DeepCloneInsertBackAllSiblings(mapRomHeader.RootElement(), &eventPage, eventPage.RootElement()->FirstChildElement("event_commands"));

            eventPage.SaveFile("playground/event.xml");

            // Fill event-page with map-rom-label commands
            tinyxml2::XMLDocument mapRomLabel;
            mapRomLabel.LoadFile((FOLDERS::TEMPLATE_PATH + "map_rom_label.xml").c_str());
            for(int labelID = 1; labelID < (numLabels + 1); ++labelID) {
                int firstVar = packVariable(gbFile.getBytes(MEMORYSIZE::BYTES_PER_VAR));
                // Second Variable is overhead for the case that a 2-Byte R/W Op needs the last Byte of the first Var and the next byte.
                int secondVar = packVariable(gbFile.peekBytes(MEMORYSIZE::BYTES_PER_VAR));
                setupMapRomLabel(&mapRomLabel, labelID, firstVar, secondVar);
                DeepCloneInsertBackAllSiblings(mapRomLabel.RootElement(), &eventPage, eventPage.RootElement()->FirstChildElement("event_commands"));
            }

            // Set Event Page ID
            eventPage.RootElement()->SetAttribute("id", generateID(pageID).c_str());

            // Insert event-page into event
            DeepCloneInsertBack(eventPage.RootElement(), &event, event.RootElement()->FirstChildElement("pages"));
        }

        // Set Event ID, Name and Coordinate
        std::string name = string("ROM") + generateID(eventID - MEMORYSIZE::MAP_ROM_ID + 1);
        int xCoord = (eventID - 1) % RPGMAKER::MAP_SIZE_X;
        int yCoord = (eventID - 1) / RPGMAKER::MAP_SIZE_Y;
        setEventIDNameCoord(&event, eventID, name, xCoord, yCoord);

        // Insert event into map
        DeepCloneInsertBack(event.RootElement(), mapDoc, 
            mapDoc->FirstChildElement("LMU")->FirstChildElement()->FirstChildElement("events"));
    }
}

void Map::generateMapRAM() {
    // load event template (event/event.xml)
    tinyxml2::XMLDocument event;
    event.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event.xml").c_str());
    // add one event-page from template (event/event_page.xml)
    tinyxml2::XMLDocument eventPage;
    eventPage.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event_page.xml").c_str());

    // insert event-page into event.
    DeepCloneInsertBack(eventPage.RootElement(), &event, 
        event.RootElement()->FirstChildElement("pages"));

    // Insert event into map
    for (int i = 0; i < MEMORYSIZE::NUM_DMG_RAM_EVENTS; ++i) {

        // Set Event ID, Name and Coordinate
        std::string name = string("RAM") + generateID(i + 1);
        int eventID = mapRAMID + i;
        int xCoord = (eventID - 1) % RPGMAKER::MAP_SIZE_X;
        int yCoord = (eventID - 1) / RPGMAKER::MAP_SIZE_Y;
        setEventIDNameCoord(&event, eventID, name, xCoord, yCoord);

        DeepCloneInsertBack(event.RootElement(), mapDoc, 
            mapDoc->FirstChildElement("LMU")->FirstChildElement()->FirstChildElement("events"));
    }
}

// Setup and Helper Functions.
void Map::setEventIDNameCoord(tinyxml2::XMLDocument* event, int id, std::string& name, int x, int y) {
    assert(x >= 0 && x < 500);
    assert(y >= 0 && y < 500);

    // Set Event ID
    event->RootElement()->SetAttribute("id", generateID(id).c_str());

    // Set Event Name
    auto* nameElem = event->RootElement()->FirstChildElement("name")->FirstChild()->ToText();
    nameElem->SetValue((name).c_str());

    // Set Event Coordinates
    auto* xCoord = event->RootElement()->FirstChildElement("x")->FirstChild();
    xCoord->SetValue(to_string((id - 1) % RPGMAKER::MAP_SIZE_X).c_str());

    auto* yCoord = event->RootElement()->FirstChildElement("y")->FirstChild();
    yCoord->SetValue(to_string((id - 1) / RPGMAKER::MAP_SIZE_Y).c_str());
}

void Map::changeCommandParameters(tinyxml2::XMLNode* command, std::string parameter) {
    auto* parameters = command->FirstChildElement("parameters")->FirstChild()->ToText();
    parameters->SetValue(parameter.c_str());
}

void Map::setupMapRomHeader(tinyxml2::XMLDocument* mapRomHeader, int numLabels) {
    // Need to change the boilerplate code (see map_rom_header.xml for details).
    // ByteOffset = (ByteOffset / BYTES_PER_VAR):
    auto* command = mapRomHeader->RootElement()->NextSiblingElement("EventCommand");
    stringstream valuestr;
    valuestr << "0 " << RPGMAKER::BYTE_OFFSET_ID << " " << RPGMAKER::BYTE_OFFSET_ID << " 4 0 " << to_string(MEMORYSIZE::BYTES_PER_VAR) << " 0";
    changeCommandParameters(command, valuestr.str());

    // LabelID = ByteOffset
    command = command->NextSiblingElement("EventCommand");
    valuestr.str(string());
    valuestr << "0 " << RPGMAKER::LABEL_ID << " " << RPGMAKER::LABEL_ID << " 0 1 " << RPGMAKER::BYTE_OFFSET_ID << " 0";
    changeCommandParameters(command, valuestr.str());

    // LabelID += 1:
    command = command->NextSiblingElement("EventCommand");
    valuestr.str(string());
    valuestr << "0 " << RPGMAKER::LABEL_ID << " " << RPGMAKER::LABEL_ID << " 1 0 " << to_string(1) << " 0";
    changeCommandParameters(command, valuestr.str());

    // JumpToLabel numLabels / 2
    command = command->NextSiblingElement("EventCommand");
    changeCommandParameters(command, to_string(numLabels / 2));
}

void Map::setupMapRomLabel(tinyxml2::XMLDocument* mapRomLabel, int labelID, int firstVar, int secondVar) {
    // Need to change the boilerplate code (see map_rom_label.xml for details).
    // Label X
    auto* command = mapRomLabel->RootElement();
    changeCommandParameters(command, to_string(labelID));

    // IF(LabelID < X)
    command = command->NextSiblingElement("EventCommand");
    stringstream valuestr;
    valuestr << "1 " << RPGMAKER::LABEL_ID << " 0 " << labelID << " 4 0";
    changeCommandParameters(command, valuestr.str());
    

    // JumpToLabel X - (min(X, 1.000 - X) / 2)
    command = command->NextSiblingElement("EventCommand");
    float minDistance = min(labelID, 1000 - labelID);
    int newID = labelID - ceil(minDistance/2.0f);
    changeCommandParameters(command, to_string(newID));

    // IF(LabelID > X)
    command = command->NextSiblingElement("EventCommand")->NextSiblingElement("EventCommand")->NextSiblingElement("EventCommand");
    valuestr.str(string());
    valuestr << "1 " << RPGMAKER::LABEL_ID << " 0 " << labelID << " 3 0";
    changeCommandParameters(command, valuestr.str());

    // JumpToLabel X + (min(X, 1.000 - X) / 2)
    command = command->NextSiblingElement("EventCommand");
    newID = labelID + ceil(minDistance/2.0f);
    changeCommandParameters(command, to_string(newID));

    // READVAR1 = LABELXVALUE1
    command = command->NextSiblingElement("EventCommand")->NextSiblingElement("EventCommand")->NextSiblingElement("EventCommand");
    // For testing!
    valuestr.str(string());
    valuestr << "0 " << RPGMAKER::READ_VAR_1 << " " << RPGMAKER::READ_VAR_1 << " 0 0 " << firstVar << " 0";
    changeCommandParameters(command, valuestr.str());

    // READVAR2 = LABELXVALUE2
    command = command->NextSiblingElement("EventCommand");
    valuestr.str(string());
    valuestr << "0 " << RPGMAKER::READ_VAR_2 << " " << RPGMAKER::READ_VAR_2 << " 0 0 " << secondVar << " 0";
    changeCommandParameters(command, valuestr.str());
}