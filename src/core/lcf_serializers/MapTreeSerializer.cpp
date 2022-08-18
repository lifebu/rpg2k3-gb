#include "MapTreeSerializer.h"

#include "Templates.h"
#include "map_tree/MapInfoSerializer.h"

#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>

namespace lcf {

MapTreeSerializer::MapTreeSerializer() {}

MapTree MapTreeSerializer::FromFile(std::string fileName) {
    return MapTree(0);
}

std::string generateTreeOrderString(int numOfMaps) {
    std::string treeOrderString = "0 ";
    for (int id = 1; id <= numOfMaps; ++id) {
        std::string emptySpace = id != numOfMaps ? " " : "";
        treeOrderString.append(std::to_string(id) + emptySpace);
    }

    return treeOrderString;
}

void MapTreeSerializer::ToFile(std::string fileName, MapTree& mapTree) {
    tinyxml2::XMLDocument mapTreeTempl(TEMPLATES::MAP_TREE);

    // Insert map infos in to the maptree.
    for(auto& mapInfo : mapTree.mapInfos) {
        auto mapInfoDoc = MapInfoSerializer().ToFile(mapInfo);

        mapInfoDoc->DeepCloneInsertBack(&mapTreeTempl, mapTreeTempl.TraverseElement("/LMT/TreeMap/maps"));
    }

    // Change the tree orders in the map.
    std::string treeOrderString = generateTreeOrderString(mapTree.mapInfos.size());
    auto* treeOrderName = mapTreeTempl.TraverseElement("/LMT/TreeMap/tree_order")->FirstChild()->ToText();
    treeOrderName->SetValue(treeOrderString.c_str());

    mapTreeTempl.SaveFile(fileName.c_str(), false);
}

};
