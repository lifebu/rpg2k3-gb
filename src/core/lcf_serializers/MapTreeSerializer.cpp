#include "MapTreeSerializer.h"

#include "Templates.h"

#include "utilities/RPGHelper.h"
#include "structure/Logger.h"

#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>
#include <memory>

namespace lcf {

MapTree MapTreeSerializer::FromFile(std::string fileName) 
{
    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) 
    {
        Logger::Get()->Log(file.ErrorStr(), LogLevel::ERROR);
        return MapTree(0);
    }

    MapTree mapTree = MapTree(0);

    // We skip the mapinfo root.
    auto* currentMapInfo = file.TraverseElement("/LMT/TreeMap/maps/MapInfo")->NextSiblingElement();
    while(currentMapInfo)
    {
        MapInfo newMapInfo = MapInfoFromFileImpl(currentMapInfo);
        mapTree.addMapInfo(newMapInfo);
        currentMapInfo = currentMapInfo->NextSiblingElement();
    }

    return mapTree;
}

void MapTreeSerializer::ToFile(std::string fileName, MapTree& mapTree) 
{
    tinyxml2::XMLDocument mapTreeTempl(TEMPLATES::MAP_TREE);
    tinyxml2::XMLDocument mapInfoTempl(TEMPLATES::MAP_INFO);

    // Insert map infos in to the maptree.
    for(auto& mapInfo : mapTree.mapInfos) 
    {
        auto* mapInfoElement = mapInfoTempl.TraverseElement("/MapInfo");
        MapInfoToFileImpl(mapInfo, mapInfoElement);

        mapInfoElement->DeepCloneInsertBack(&mapTreeTempl, mapTreeTempl.TraverseElement("/LMT/TreeMap/maps"));
    }

    // Change the tree orders in the map.
    std::string treeOrderString = generateTreeOrderString(mapTree.mapInfos.size());
    auto* treeOrderName = mapTreeTempl.TraverseElement("/LMT/TreeMap/tree_order")->FirstChild()->ToText();
    treeOrderName->SetValue(treeOrderString.c_str());

    mapTreeTempl.SaveFile(fileName.c_str(), false);
    if (mapTreeTempl.Error()) 
    {
        Logger::Get()->Log(mapTreeTempl.ErrorStr(), LogLevel::ERROR);
    }
}

MapInfo MapTreeSerializer::MapInfoFromFileImpl(tinyxml2::XMLElement* mapInfo)
{
    // Get Map ID
    uint16_t id = mapInfo->IntAttribute("id");

    // Get map name.
    auto* nameElem = mapInfo->TraverseElement("/name")->FirstChild()->ToText();
    std::string name = (nameElem == nullptr) ? "" : nameElem->Value();

    return MapInfo(id, name);
}

void MapTreeSerializer::MapInfoToFileImpl(const MapInfo& elem, tinyxml2::XMLElement* mapInfo)
{
    // Set Map ID
    mapInfo->SetAttribute("id", generateID(elem.id).c_str());

    // Change map name to filename.
    auto* nameElem = mapInfo->TraverseElement("/name")->FirstChild()->ToText();
    nameElem->SetValue(elem.name.c_str());
}

std::string MapTreeSerializer::generateTreeOrderString(int numOfMaps) 
{
    std::string treeOrderString = "0 ";

    for (int id = 1; id <= numOfMaps; ++id) 
    {
        std::string emptySpace = id != numOfMaps ? " " : "";
        treeOrderString.append(std::to_string(id) + emptySpace);
    }

    return treeOrderString;
}

};
