#include "Database.h"

#include "Globals.h"

#include "src/core/lcf/Database.h"
#include "src/core/lcf_serializers/DatabaseSerializer.h"

#include <tuple>
#include <iostream>
#include <fstream>

using namespace gb2rpg;

const static std::string WARN_NO_SWITCH_NAMES = "Info: Could not find 'project/switch_names.txt'. Using default names for switches instead.\n";
const static std::string WARN_NO_VAR_NAMES = "Info: Could not find 'project/var_names.txt'. Using default names for variables instead.\n";
const static std::string WARN_NO_COMMON_EVENTS = "Info: Could not find 'project/common_events.xml'. Skipping common events.\n";



// public
void Database::genDatabase() {
    lcf::Database database;

    std::cout << "Generating Database: RPG_RT.edb\n";

    genSwitches(database);
    genVariables(database);
    genItems(database);
    genCharacters(database);
    //genCommonEvents(database);

    lcf::DatabaseSerializer::ToFile(PROJECT::PROJECT_DIR + EXPORTS::DATABASE_FILE, database);
}

void Database::genSwitches(lcf::Database& database) {
    std::ifstream nameFile(PROJECT::PROJECT_DIR + PROJECT::SWITCH_NAMES);
    if(!nameFile.is_open()) std::cout << WARN_NO_SWITCH_NAMES;

    for(int id = 1; id < RPGMAKER::MAX_NUM_SWITCHES; ++id) {
        // Use a file that supplies names or use default names.
        std::string name = "SW" + generateID(id);
        if(nameFile.is_open()) nameFile >> name;

        database.addSwitch(name);
    }
}

void Database::genVariables(lcf::Database& database) {
    std::ifstream nameFile(PROJECT::PROJECT_DIR + PROJECT::SWITCH_NAMES);
    if(!nameFile.is_open()) std::cout << WARN_NO_VAR_NAMES;

    for(int id = 1; id < RPGMAKER::MAX_NUM_VARIABLES; ++id) {
        // Use a file that supplies names or use default names.
        std::string name = "VAR" + generateID(id);
        if(nameFile.is_open()) nameFile >> name;

        database.addVariable(name);
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
        return std::tuple(RPGMAKER::HEAD_ID, id - 6144);
    
    } else if (id > 8192 && id <= 9216) {
        return std::tuple(RPGMAKER::ACCESSORY_ID, id - 8192);
    
    } else {
        return std::tuple(0, 0);
    }  
}

void Database::genItems(lcf::Database& database) {
    for (int id = 1; id < RPGMAKER::MAX_NUM_ITEMS; ++id) {
        // Only add items that we actually need to store character data.
        if (id > MEMORYSIZES::TOTAL_USED_ITEMS) break;

        // create the name, and typeID
        auto[typeID, localID] = getItemTypeAndLocalID(id);
        std::string name = RPGMAKER::ITEM_NAMES[typeID] + generateID(localID);

        database.addItem(name, static_cast<lcf::ItemType>(typeID));
    }
}

void Database::genCharacters(lcf::Database& database) {
    for (int id = 1; id < RPGMAKER::MAX_NUM_CHARS; ++id) {
        std::string name = "CHAR" + generateID(id);

        database.addCharacter(name);
    }
}

void Database::genCommonEvents(lcf::Database& database) {
    // TODO: read the common event file (parse it with) and add each common event to the database.
    /*
    tinyxml2::XMLDocument commonEvents((PROJECT::PROJECT_DIR + PROJECT::COMMON_EVENTS).c_str());
    if(commonEvents.ErrorID() == tinyxml2::XML_ERROR_FILE_NOT_FOUND)
        std::cout << WARN_NO_COMMON_EVENTS;
    
    if(!commonEvents.Error()) {

        commonEvents.DeepCloneInsertBackSiblings(&databaseDoc, databaseDoc.TraverseElement("/LDB/Database/commonevents"));
    }
    */
}