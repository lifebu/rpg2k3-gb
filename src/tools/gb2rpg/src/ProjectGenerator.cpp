#include "ProjectGenerator.h"

#include "Map.h"
#include "MapTree.h"
#include "Database.h"

#include <string>

void genProjectFolder(std::vector<Map>& maps, MapTree& mapTree, Database& database) {
    for(int i = 0; i < maps.size(); ++i) {
        // TODO: For more than 9 gb files this needs to be better, but is good enough for now!
        std::string mapID = std::string("000") + std::to_string(i + 1);
        maps.at(i).exportXML("playground/Map" + mapID + ".emu");
    }
}