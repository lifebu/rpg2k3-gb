#include "Database.h"

#include "Globals.h"

#include "thirdparty/tinyxml2/tinyxml2.h"
#include "src/core/utilities/RPGHelper.h"

#include <tuple>

// public
void Database::genDatabase() {
    tinyxml2::XMLDocument databaseDoc(TEMPLATES::DATABASE);
    
    genSwitches(databaseDoc);
    genVariables(databaseDoc);
    genItems(databaseDoc);
    genCharacters(databaseDoc);

    databaseDoc.SaveFile(EXPORTS::DATABASE, false);
}

void Database::genSwitches(tinyxml2::XMLDocument& databaseDoc) {
    tinyxml2::XMLDocument switchDoc(TEMPLATES::SWITCH);

    for(int id = 1; id < RPGMAKER::MAX_NUM_SWITCHES; ++id) {
        switchDoc.RootElement()->SetAttribute("id", generateID(id).c_str());

        // TODO: Names are placeholder right now, later it would make sense that you can supply names to make the RPG Maker code more readable.
        auto* name = switchDoc.TraverseElement("/Switch/name")->FirstChild()->ToText();
        name->SetValue(std::string("SW" + generateID(id)).c_str());

        switchDoc.DeepCloneInsertBack(&databaseDoc, databaseDoc.TraverseElement("/LDB/Database/switches"));
    }
}

void Database::genVariables(tinyxml2::XMLDocument& databaseDoc) {
    tinyxml2::XMLDocument variableDoc(TEMPLATES::VARIABLE);

    for(int id = 1; id < RPGMAKER::MAX_NUM_VARIABLES; ++id) {
        variableDoc.RootElement()->SetAttribute("id", generateID(id).c_str());

        // TODO: Names are placeholder right now, later it would make sense that you can supply names to make the RPG Maker code more readable.
        auto* name = variableDoc.TraverseElement("/Variable/name")->FirstChild()->ToText();
        name->SetValue(std::string("VAR" + generateID(id)).c_str());

        variableDoc.DeepCloneInsertBack(&databaseDoc, databaseDoc.TraverseElement("/LDB/Database/variables"));
    }
}

// Generate the Type IDs and the local IDs required for the correct names and type IDs of the item.
std::tuple<int, int> constexpr getItemTypeAndLocalID(int id) {
    // TODO: the lower and upper bounds should be calculated using MEMORYSIZES::NUM_OF_*. makes this configureable!
    if(id >= 1 && id <= 2048) {
        return std::tuple(RPGMAKER::WEAPON_ID, id);
    
    } else if (id > 2048 && id <= 4096) {
        return std::tuple(RPGMAKER::SHIELD_ID, id - 2048);
    
    } else if (id > 4096 && id <= 6144) {
        return std::tuple(RPGMAKER::BODY_ID, id - 4096);
    
    } else if (id > 6144 && id <= 8192) {
        return std::tuple(RPGMAKER::SHIELD_ID, id - 6144);
    
    } else if (id > 8192 && id <= 9216) {
        return std::tuple(RPGMAKER::ACCESSORY_ID, id - 8192);
    
    } else {
        return std::tuple(0, 0);
    }  
}

void Database::genItems(tinyxml2::XMLDocument& databaseDoc) {
    tinyxml2::XMLDocument itemDoc(TEMPLATES::ITEM);

    for (int id = 1; id < RPGMAKER::MAX_NUM_ITEMS; ++id) {
        // Only add items that we actually need to store character data.
        if (id > MEMORYSIZES::TOTAL_USED_ITEMS) break;

        itemDoc.RootElement()->SetAttribute("id", generateID(id).c_str());

        auto[typeID, localID] = getItemTypeAndLocalID(id);

        // E.g. WPN0001, BODY0012
        auto* name = itemDoc.TraverseElement("/Item/name")->FirstChild()->ToText();
        name->SetValue((RPGMAKER::ITEM_NAMES[typeID] + generateID(localID)).c_str());

        // Weapon = 1, Shield = 2, etc (see: RPGMaker.h, WEAPON_ID, SHIELD_ID,...)
        auto* type = itemDoc.TraverseElement("/Item/type")->FirstChild()->ToText();
        type->SetValue(std::to_string(typeID).c_str());

        itemDoc.DeepCloneInsertBack(&databaseDoc, databaseDoc.TraverseElement("/LDB/Database/items"));
    }
}

void Database::genCharacters(tinyxml2::XMLDocument& databaseDoc) {
    tinyxml2::XMLDocument charDoc(TEMPLATES::CHARACTER);

    for (int id = 1; id < RPGMAKER::MAX_NUM_CHARS; ++id) {
        charDoc.RootElement()->SetAttribute("id", generateID(id).c_str());

        auto* name = charDoc.TraverseElement("/Actor/name")->FirstChild()->ToText();
        name->SetValue(std::string("CHAR" + generateID(id)).c_str());

        charDoc.DeepCloneInsertBack(&databaseDoc, databaseDoc.TraverseElement("/LDB/Database/actors"));
    }
}