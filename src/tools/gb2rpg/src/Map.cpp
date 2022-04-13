#include "Map.h"

#include "GBFile.h"
#include "Globals.h"

#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>
#include <cstdio>

using namespace std;

// public
Map::Map(GBFile& gbFile)
    : events(nullptr), nextEventID(1) {
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

    events = new tinyxml2::XMLDocument;
    
    generateMapROM(gbFile);
    generateMapRAM();
}
Map::~Map() {
    mapTemplateRefCount--;
    if (mapTemplateRefCount == 0) {
        delete mapTemplate;
        mapTemplate = nullptr;
    }

    if(events) {
        delete events;
        events = nullptr;
    }
}

/*
Map::Map(const Map& other) {
    // refcounting for templates
    mapTemplateRefCount++;
    dmgTemplateRefCount++;

    if(!other.events) {
        events = nullptr;
        return;
    }
    // other has loaded an events XML Document that we also want.
    events = other.events;
    other.events = nullptr;
}
*/

void Map::exportXML(std::string filePath) {
    // 1st: Map
    // create new XMLDocument (map)
    // load it with the map-template

    // 2nd: DMG-ROM:
    // load event template
    // fill it with dmg_rom (event_commands)
    // add dmg_event to map

    // 3rd: events: MAP-ROM & MAP-RAM:
    // this.events contains all the MAP-ROM & MAP-RAM events
    // add events to map

    // 4th: map.SaveFile(filePath);
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
void Map::generateMapROM(GBFile& gbFile) {
    // for loop (o to numberofEvents)
        // load event template (event/event.xml)
        // for loop (o to 100 event pages)
            // load event-page template (event/event_page).
            // Fill Event Commands:
            // 1st: Fill event-page.commands with template map/map_rom_header.xml
            // 2nd: for loop (o to VARS_PER_EPAGE)
                // load template map/map_rom_label.xml
                // change values required
                // deep copy to event-page.commands
            // deep copy event-page into event
        // deep copy event into this.events
}
void Map::generateMapRAM() {
    // load event template (event/event.xml)
    // add one event-page from template (event/event_page.xml)
    // for loop (0 to MEMORYSIZE::NUM_DMG_RAM_EVENTS, increment nextEventID on loop)

        // change event ID in loaded template
        // deep copy it into this.events
}