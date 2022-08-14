#include "DatabaseSerializer.h"

#include "Templates.h"
#include "database/LCFTypeSerializer.h"
#include "database/ItemSerializer.h"
#include "database/CharacterSerializer.h"
#include "database/CommonEventSerializer.h"

#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>

namespace lcf {



Database DatabaseSerializer::FromFile(std::string fileName) {
    return Database();
}

void DatabaseSerializer::ToFile(std::string fileName, Database& database) {
    tinyxml2::XMLDocument databaseTempl(TEMPLATES::DATABASE);

    // Switches
    for(auto& switchElem : database.switches) {
        auto switchDoc = SwitchSerializer().ToFile(switchElem);

        switchDoc->DeepCloneInsertBack(&databaseTempl, databaseTempl.TraverseElement("/LDB/Database/switches"));
    }

    // Variables
    for(auto& variableElem : database.variables) {
        auto variableDoc = VariableSerializer().ToFile(variableElem);

        variableDoc->DeepCloneInsertBack(&databaseTempl, databaseTempl.TraverseElement("/LDB/Database/variables"));
    }

    // Items
    for(auto& itemElem : database.items) {
        auto itemDoc = ItemSerializer::ToFile(itemElem);

        itemDoc->DeepCloneInsertBack(&databaseTempl, databaseTempl.TraverseElement("/LDB/Database/items"));
    }

    // Characters
    for(auto& characterElem : database.characters) {
        auto characterDoc = CharacterSerializer::ToFile(characterElem);

        characterDoc->DeepCloneInsertBack(&databaseTempl, databaseTempl.TraverseElement("/LDB/Database/actors"));
    }

    // Common Events
    for(auto& commonEventsElem : database.commonEvents) {
        auto commonEventDoc = CommonEventSerializer::ToFile(commonEventsElem);

        commonEventDoc->DeepCloneInsertBack(&databaseTempl, databaseTempl.TraverseElement("/LDB/Database/commonevents"));
    }


    databaseTempl.SaveFile(fileName.c_str(), false);
}

};
