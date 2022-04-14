#include "Map.h"

#include "GBFile.h"
#include "Globals.h"

#include "thirdparty/tinyxml2/tinyxml2.h"
#include "tinyxml2_helper.h"

#include <iostream>
#include <cstdio>

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
    tinyxml2::XMLDocument event;
    event.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event.xml").c_str());

    tinyxml2::XMLDocument eventPage;
    eventPage.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event_page.xml").c_str());

    tinyxml2::XMLDocument DMGROM;
    DMGROM.LoadFile((FOLDERS::TEMPLATE_PATH + "dmg_rom.xml").c_str());
    

    // add DMGROM into event-page
    DeepCloneInsertBackAllSiblings(DMGROM.RootElement(), &eventPage,
        eventPage.RootElement()->FirstChildElement("event_commands"));

    // insert event-page into event.
    DeepCloneInsertBack(eventPage.RootElement(), &event, 
        event.RootElement()->FirstChildElement("pages"));

    // insert DMG Event into map
    DeepCloneInsertBack(event.RootElement(), mapDoc, 
        mapDoc->FirstChildElement("LMU")->FirstChildElement()->FirstChildElement("events"));
}
void Map::generateMapROM(GBFile& gbFile) {
    int numOfMapROMs = ((gbFile.getRomSize() * 1024) / (MEMORYSIZE::MAX_PAGES_PER_EVENT * MEMORYSIZE::BYTES_PER_EPAGE)) + 1;

    // create all necessary ROM Events
    for(int eventID = MEMORYSIZE::MAP_ROM_ID; eventID < MEMORYSIZE::MAP_ROM_ID + numOfMapROMs; ++eventID) {
        tinyxml2::XMLDocument event;
        event.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event.xml").c_str());
        // TODO NEED EARLY BREAK IF WE HAVE ENOUGH ROM DATA (Can do that with EOF for gbFile).
        for (int pageID = 1; pageID < 101; ++pageID) {
            tinyxml2::XMLDocument eventPage;
            eventPage.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event_page.xml").c_str());

            // Fill event-page with map-rom-header commands
            tinyxml2::XMLDocument mapRomHeader;
            mapRomHeader.LoadFile((FOLDERS::TEMPLATE_PATH + "map_rom_header.xml").c_str());

            DeepCloneInsertBackAllSiblings(mapRomHeader.RootElement(), &eventPage, eventPage.RootElement()->FirstChildElement("event_commands"));


            // Fill event-page with map-rom-label commands
            tinyxml2::XMLDocument mapRomLabel;
            mapRomLabel.LoadFile((FOLDERS::TEMPLATE_PATH + "map_rom_label.xml").c_str());
            for(int labelID = 1; labelID < 1001; ++labelID) {
                DeepCloneInsertBackAllSiblings(mapRomLabel.RootElement(), &eventPage, eventPage.RootElement()->FirstChildElement("event_commands"));
            }

            // Insert event-page into event
            DeepCloneInsertBack(eventPage.RootElement(), &event, event.RootElement()->FirstChildElement("pages"));
        }

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

    // insert events with changed id's.
    for (int i = 0; i < MEMORYSIZE::NUM_DMG_RAM_EVENTS; ++i) {  
        event.RootElement()->SetAttribute("id", generateID(mapRAMID + i).c_str());
        DeepCloneInsertBack(event.RootElement(), mapDoc, 
            mapDoc->FirstChildElement("LMU")->FirstChildElement()->FirstChildElement("events"));
    }
}