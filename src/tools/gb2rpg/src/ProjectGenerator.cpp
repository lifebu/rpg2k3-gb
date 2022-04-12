#include "ProjectGenerator.h"

#include "Map.h"
#include "MapTree.h"
#include "Database.h"

void genProjectFolder(std::vector<Map>& maps, MapTree& mapTree, Database& database) {
    for(auto& map : maps) {
        map.exportXML("");
    }
}