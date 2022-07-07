#include "MapTree.h"

#include "GBFile.h"
#include "Globals.h"

#include "thirdparty/tinyxml2/tinyxml2.h"
#include "src/core/utilities/RPGHelper.h"

#include <cassert>

void MapTree::genMapTree(std::vector<GBFile>& gbFiles) {
    tinyxml2::XMLDocument mapTreeDoc(TEMPLATES::MAP_TREE);

    // the map tree needs a ordered list of the map ids.
    std::string treeOrderString = "0 ";

    for (int id = 1; id <= gbFiles.size(); ++id) {
        tinyxml2::XMLDocument mapInfo(TEMPLATES::MAP_INFO);

        // Set Map ID
        mapInfo.RootElement()->SetAttribute("id", generateID(id).c_str());

        // Append the map ID to the treeOrder.
        std::string emptySpace;
        if (id != gbFiles.size()) emptySpace = " ";
        treeOrderString.append(std::to_string(id) + emptySpace);

        // Change map name to filename.
        auto* name = mapInfo.TraverseElement("/MapInfo/name")->FirstChild()->ToText();
        name->SetValue(gbFiles.at(id - 1).getTitle().c_str());

        // Insert map info in to the maptree.
        mapInfo.DeepCloneInsertBack(&mapTreeDoc, mapTreeDoc.TraverseElement("/LMT/TreeMap/maps"));
    }

    // Change the tree orders in the map.
    auto* treeOrderName = mapTreeDoc.TraverseElement("/LMT/TreeMap/tree_order")->FirstChild()->ToText();
    treeOrderName->SetValue(treeOrderString.c_str());


    mapTreeDoc.SaveFile(EXPORTS::MAP_TREE.c_str(), false);
}