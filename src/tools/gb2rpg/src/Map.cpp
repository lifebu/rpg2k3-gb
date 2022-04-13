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
    // load template files and manage refcounts
    if(!mapTemplate) {
        mapTemplate = new tinyxml2::XMLDocument;
        mapTemplateRefCount = 1;
        mapTemplate->LoadFile((FOLDERS::TEMPLATE_PATH + "map/map.xml").c_str());
    } else {
        mapTemplateRefCount++;
    }

    if(!dmgTemplate) {
        dmgTemplate = new tinyxml2::XMLDocument;
        dmgTemplateRefCount = 1;
        dmgTemplate->LoadFile((FOLDERS::TEMPLATE_PATH + "dmg_rom.xml").c_str());
    } else {
        dmgTemplateRefCount++;
    }

    // TODO: as map already has <events></events> I do not need to use a template here!
    events = new tinyxml2::XMLDocument;
    events->LoadFile((FOLDERS::TEMPLATE_PATH + "map/map_events.xml").c_str());
    
    generateMapROM(gbFile);
    generateMapRAM();
}
Map::~Map() {
    mapTemplateRefCount--;
    if (mapTemplateRefCount == 0) {
        delete mapTemplate;
        mapTemplate = nullptr;
    }
    dmgTemplateRefCount--;
    if (dmgTemplateRefCount == 0) {
        delete dmgTemplate;
        dmgTemplate = nullptr;
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
    
}
void Map::generateMapRAM() {
    // load template (event/event.xml)
    // for loop (0 to MEMORYSIZE::NUM_DMG_RAM_EVENTS, increment nextEventID on loop)
    // change event ID in loaded template
    // copy it into this.events (DEEP COPY NEEDED!)
}