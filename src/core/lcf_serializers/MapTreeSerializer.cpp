#include "MapTreeSerializer.h"

#include "Templates.h"
#include "MapInfoSerializer.h"

#include "src/core/utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>

namespace lcf {



// TODO: Implement (should use MapInfoSerializer unique_ptr<XMLDocument> FromFile()) like ToFile does!
MapTree MapTreeSerializer::FromFile(std::string fileName) {
    /*
    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) {
        std::cout << file.ErrorStr() << std::endl;
        return MapTree(0);
    }

    file

    MapTree mapTree(numMaps);

    std::vector<MapInfo> infos;
    */


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
        auto mapInfoDoc = MapInfoSerializer::ToFile(mapInfo);

        mapInfoDoc->DeepCloneInsertBack(&mapTreeTempl, mapTreeTempl.TraverseElement("/LMT/TreeMap/maps"));
    }

    // Change the tree orders in the map.
    std::string treeOrderString = generateTreeOrderString(mapTree.mapInfos.size());
    auto* treeOrderName = mapTreeTempl.TraverseElement("/LMT/TreeMap/tree_order")->FirstChild()->ToText();
    treeOrderName->SetValue(treeOrderString.c_str());

    mapTreeTempl.SaveFile(fileName.c_str(), false);
}

};
