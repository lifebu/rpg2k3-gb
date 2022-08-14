#include "Map.h"

#include "GBFile.h"
#include "Globals.h"

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

        lcf::Map map;

        generateDMGROM(map);
        generateMapROM(map, gbFile, numOfMapROMs);
        generateMapRAM(map);

        lcf::MapSerializer::ToFile(filePath, map);
    }
}

// private
void Map::generateDMGROM(lcf::Map& map) {
    lcf::Event& event = map.addEvent("DMGROM", 0, 0);
    lcf::EventPage& eventPage = event.addEventPage();

    std::vector<lcf::EventCommand> DMGCommands = lcf::EventCommandSerializer::MultipleFromFile(TEMPLATES::DMG_ROM);
    eventPage.addEventCommands(DMGCommands);
}

void Map::generateMapROM(lcf::Map& map, GBFile& gbFile, int numOfMapROMs) {
    // pre-load data
    std::vector<lcf::EventCommand> mapRomHeader = lcf::EventCommandSerializer::MultipleFromFile(TEMPLATES::MAP_ROM_HEADER);
    std::vector<lcf::EventCommand> mapRomLabel = lcf::EventCommandSerializer::MultipleFromFile(TEMPLATES::MAP_ROM_LABEL);
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
            // TODO: once eventCommandSerializer is implemented!
            //setupMapRomHeader(mapRomHeader, numLabels);
            eventPage.addEventCommands(mapRomHeader);

            // Fill event-page with map-rom-label commands
            for (int labelID = 1; labelID <= numLabels; ++labelID) {
                int firstVar = packVariable(gbFile.getBytes(MEMORYSIZES::BYTES_PER_VAR));
                int secondVar = packVariable(gbFile.peekBytes(MEMORYSIZES::BYTES_PER_VAR));
                if(lastEventPage && labelID == numLabels) {
                    // Second variable should indicate garbage value, as it contains data after the GBFile. 
                    secondVar = -9999999;
                }

                // TODO: once eventCommandSerializer is implemented!
                //setupMapRomLabel(mapRomLabel, labelID, numLabels, firstVar, secondVar);
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
    // TODO: This is not great code But I have not yet settled on a good way to change the commands.
    assert(mapRomHeader.size() == 4);

    // Need to change the boilerplate code (see map_rom_header.xml for details).
    // ByteOffset = (ByteOffset / BYTES_PER_VAR):
    mapRomHeader.at(0).setParameters({7, 0, VARMAPPING::BYTE_OFFSET_ID, VARMAPPING::BYTE_OFFSET_ID, 4, 0, MEMORYSIZES::BYTES_PER_VAR, 0});

    // LabelID = ByteOffset
    mapRomHeader.at(1).setParameters({7, 0, VARMAPPING::LABEL_ID, VARMAPPING::LABEL_ID, 0, 1, VARMAPPING::BYTE_OFFSET_ID, 0});

    // LabelID = ByteOffset
    mapRomHeader.at(2).setParameters({7, 0, VARMAPPING::LABEL_ID, VARMAPPING::LABEL_ID, 1, 0, 1, 0});

    // LabelID = ByteOffset
    mapRomHeader.at(4).setParameters({1, numLabels / 2});
}

void Map::setupMapRomLabel(std::vector<lcf::EventCommand>& mapRomLabel, int labelID, int numLabels, int firstVar, int secondVar) {
    // TODO: This is not great code But I have not yet settled on a good way to change the commands.
    assert(mapRomLabel.size() == 7);

    // Need to change the boilerplate code (see map_rom_label.xml for details).
    // Label X
    mapRomLabel.at(0).setParameters({1, labelID});

    // IF(LabelID < X)
    mapRomLabel.at(1).setParameters({6, 1, VARMAPPING::LABEL_ID, 0, labelID, 4, 0});
    
    // JumpToLabel X - (min(X, 1.000 - X) / 2)
    float minDistance = std::min(labelID, numLabels - labelID);
    if(labelID == 1) {
        // The first MapRomLabel does not need to jump here, instead change the command to EndEventProcessing
        mapRomLabel.at(2).setType(lcf::CommandType::END_EVENT_PROCESSING);
        mapRomLabel.at(2).setParameters({0});
    } else {
        int newID = labelID - ceil(minDistance/2.0f);
        mapRomLabel.at(2).setParameters({1, newID});
    }

    // IF(LabelID > X)
    mapRomLabel.at(3).setParameters({6, 1, VARMAPPING::LABEL_ID, 0, labelID, 3, 0});

    // JumpToLabel X + (min(X, 1.000 - X) / 2)
    if(labelID == numLabels) {
        // The last MapRomLabel does not need to jump here, instead change the command to EndEventProcessing.
        mapRomLabel.at(4).setType(lcf::CommandType::END_EVENT_PROCESSING);
        mapRomLabel.at(4).setParameters({0});
    } else {
        int newID = labelID + ceil(minDistance/2.0f);
        mapRomLabel.at(4).setParameters({1, newID});
    }

    // READVAR1 = LABELXVALUE1
    mapRomLabel.at(5).setParameters({7, 0, VARMAPPING::READ_VAR_1, VARMAPPING::READ_VAR_1, 0, 0, firstVar, 0});

    // READVAR2 = LABELXVALUE2
    mapRomLabel.at(6).setParameters({7, 0, VARMAPPING::READ_VAR_2, VARMAPPING::READ_VAR_2, 0, 0, secondVar, 0});
}