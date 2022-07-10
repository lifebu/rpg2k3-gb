#include "Database.h"

#include "Globals.h"

#include "thirdparty/tinyxml2/tinyxml2.h"
#include "src/core/utilities/RPGHelper.h"

#include <tuple>
#include <iostream>
#include <fstream>

const static std::string WARN_NO_SWITCH_NAMES = "Info: Could not find 'project/switch_names.txt'. Using default names for switches instead.\n";
const static std::string WARN_NO_VAR_NAMES = "Info: Could not find 'project/var_names.txt'. Using default names for variables instead.\n";
const static std::string WARN_NO_COMMON_EVENTS = "Info: Could not find 'project/common_events.xml'. Skipping common events.\n";

// public
void Database::genDatabase() {
    tinyxml2::XMLDocument databaseDoc(TEMPLATES::DATABASE);

    std::cout << "Generating database: RPG_RT.edb\n";
    
    genSwitches(databaseDoc);
    genVariables(databaseDoc);
    genItems(databaseDoc);
    genCharacters(databaseDoc);
    genCommonEvents(databaseDoc);

    std::string filePath = PROJECT::PROJECT_DIR + EXPORTS::DATABASE_FILE;
    databaseDoc.SaveFile(filePath.c_str(), false);
}


void Database::genSwitches(tinyxml2::XMLDocument& databaseDoc) {
    tinyxml2::XMLDocument switchDoc(TEMPLATES::SWITCH);
    std::ifstream nameFile;
    nameFile.open(PROJECT::PROJECT_DIR + PROJECT::SWITCH_NAMES);
    if(!nameFile.is_open()) std::cout << WARN_NO_SWITCH_NAMES;

    for(int id = 1; id < RPGMAKER::MAX_NUM_SWITCHES; ++id) {
        switchDoc.RootElement()->SetAttribute("id", generateID(id).c_str());

        // Either use a file that supplies names for switches and variables if it exists, otherwise create default names.
        std::string name = "SW" + generateID(id);
        if(nameFile.is_open()) nameFile >> name;

        auto* nameElem = switchDoc.TraverseElement("/Switch/name")->FirstChild()->ToText();
        nameElem->SetValue(name.c_str());

        switchDoc.DeepCloneInsertBack(&databaseDoc, databaseDoc.TraverseElement("/LDB/Database/switches"));
    }
}

void Database::genVariables(tinyxml2::XMLDocument& databaseDoc) {
    tinyxml2::XMLDocument variableDoc(TEMPLATES::VARIABLE);
    std::ifstream nameFile;
    nameFile.open(PROJECT::PROJECT_DIR + PROJECT::VAR_NAMES);
    if(!nameFile.is_open()) std::cout << WARN_NO_VAR_NAMES;

    for(int id = 1; id < RPGMAKER::MAX_NUM_VARIABLES; ++id) {
        variableDoc.RootElement()->SetAttribute("id", generateID(id).c_str());

        // Either use a file that supplies names for switches and variables if it exists, otherwise create default names.
        std::string name = "VAR" + generateID(id);
        if(nameFile.is_open()) nameFile >> name;

        auto* nameElem = variableDoc.TraverseElement("/Variable/name")->FirstChild()->ToText();
        nameElem->SetValue(std::string("VAR" + generateID(id)).c_str());

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

void Database::genCommonEvents(tinyxml2::XMLDocument& databaseDoc) {
    tinyxml2::XMLDocument commonEvents((PROJECT::PROJECT_DIR + PROJECT::COMMON_EVENTS).c_str());
    if(commonEvents.ErrorID() == tinyxml2::XML_ERROR_FILE_NOT_FOUND)
        std::cout << WARN_NO_COMMON_EVENTS;
    
    if(!commonEvents.Error()) {

        commonEvents.DeepCloneInsertBackSiblings(&databaseDoc, databaseDoc.TraverseElement("/LDB/Database/commonevents"));
    }
}