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
    : eventsDoc(nullptr) {
    int numOfMapROMs = ((gbFile.getRomSize() * 1024) / (MEMORYSIZE::MAX_PAGES_PER_EVENT * MEMORYSIZE::BYTES_PER_EPAGE)) + 1;
    mapRAMID = MEMORYSIZE::MAP_ROM_ID + numOfMapROMs;

    // load template files and manage refcounts
    if(!mapTemplate) {
        mapTemplate = new tinyxml2::XMLDocument;
        mapTemplateRefCount = 1;
        mapTemplate->LoadFile((FOLDERS::TEMPLATE_PATH + "map/map.xml").c_str());
    } else {
        mapTemplateRefCount++;
    }

    eventsDoc = new tinyxml2::XMLDocument;
    generateDMGROM();
    generateMapROM(gbFile);
    generateMapRAM();
}
Map::~Map() {
    mapTemplateRefCount--;
    if (mapTemplateRefCount == 0) {
        delete mapTemplate;
        mapTemplate = nullptr;
    }

    if(eventsDoc) {
        delete eventsDoc;
        eventsDoc = nullptr;
    }
}

void Map::exportXML(std::string filePath) {
    // Load map with template.
    tinyxml2::XMLDocument map;
    DeepCloneInsertBackAllSiblings(mapTemplate->FirstChild(), &map, nullptr);

    // Insert Events:
    DeepCloneInsertBackAllSiblings(eventsDoc->RootElement(), &map, map.FirstChildElement("LMU")->FirstChildElement()->FirstChildElement("events"));

    map.SaveFile(filePath.c_str());
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
    tinyxml2::XMLDocument eventTemplate;
    eventTemplate.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event.xml").c_str());

    tinyxml2::XMLDocument eventPageTemplate;
    eventPageTemplate.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event_page.xml").c_str());

    tinyxml2::XMLDocument DMGROM;
    DMGROM.LoadFile((FOLDERS::TEMPLATE_PATH + "dmg_rom.xml").c_str());
    

    // add DMGROM into event-page
    DeepCloneInsertBackAllSiblings(DMGROM.RootElement(), &eventPageTemplate,
        eventPageTemplate.RootElement()->FirstChildElement("event_commands"));

    // insert event-page into event.
    DeepCloneInsertBack(eventPageTemplate.RootElement(), &eventTemplate, 
        eventTemplate.RootElement()->FirstChildElement("pages"));

    // insert DMG Event into map events
    DeepCloneInsertBack(eventTemplate.RootElement(), eventsDoc, 
        eventsDoc->LastChildElement());
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



        // Insert event into events
        DeepCloneInsertBack(event.RootElement(), eventsDoc, nullptr);
    }
}
void Map::generateMapRAM() {
    // load event template (event/event.xml)
    tinyxml2::XMLDocument eventTemplate;
    eventTemplate.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event.xml").c_str());
    // add one event-page from template (event/event_page.xml)
    tinyxml2::XMLDocument eventPageTemplate;
    eventPageTemplate.LoadFile((FOLDERS::TEMPLATE_PATH + "event/event_page.xml").c_str());

    // insert event-page into event.
    DeepCloneInsertBack(eventPageTemplate.RootElement(), &eventTemplate, 
        eventTemplate.RootElement()->FirstChildElement("pages"));

    // insert events with changed id's.
    for (int i = 0; i < MEMORYSIZE::NUM_DMG_RAM_EVENTS; ++i) {  
        eventTemplate.RootElement()->SetAttribute("id", generateID(mapRAMID + i).c_str());
        DeepCloneInsertBack(eventTemplate.RootElement(), eventsDoc, nullptr);
    }
}