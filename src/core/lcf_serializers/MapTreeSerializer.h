#pragma once

#include "../lcf/MapTree.h"

#include <string>

namespace tinyxml2 {class XMLDocument; class XMLElement;};

namespace lcf {

class MapTreeSerializer
{
public:
    static MapTree FromFile(std::string fileName);
    static void ToFile(std::string fileName, MapTree& mapTree);

private:
    static MapInfo MapInfoFromFileImpl(tinyxml2::XMLElement* mapInfo);
    static void MapInfoToFileImpl(const MapInfo& elem, tinyxml2::XMLElement* mapInfo);

    static std::string generateTreeOrderString(int numOfMaps);
};

};