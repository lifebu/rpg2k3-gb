#include "Map.h"

#include "GBFile.h"
#include "Globals.h"

#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>
#include <cstdio>

using namespace std;

// public
Map::Map(GBFile& gbFile)
    : events(nullptr) {
    // load template files and manage refcounts
    if(!mapTemplate) {
        mapTemplate = new tinyxml2::XMLDocument;
        mapTemplateRefCount = 1;
        mapTemplate->LoadFile((FOLDERS::templatePath + "map/map.xml").c_str());
    } else {
        mapTemplateRefCount++;
    }

    if(!dmgTemplate) {
        dmgTemplate = new tinyxml2::XMLDocument;
        dmgTemplateRefCount = 1;
        dmgTemplate->LoadFile((FOLDERS::templatePath + "dmg_rom.xml").c_str());
    } else {
        dmgTemplateRefCount++;
    }

    events = new tinyxml2::XMLDocument;
    events->LoadFile((FOLDERS::templatePath + "map/map_events.xml").c_str());
    
    generateMapROM(gbFile);
    generateMapRAM(gbFile.getRamSize());
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
    int a = 10;
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
void Map::generateMapRAM(int ramSize) {

}