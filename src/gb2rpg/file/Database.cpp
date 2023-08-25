#include "Database.h"

#include <tuple>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <core/def/Globals.h>
#include <core/def/RPGMaker.h>
#include <core/lcf/Database.h>
#include <core/lcf_serializers/DatabaseSerializer.h>
#include <core/lcf_serializers/CommonEventSerializer.h>
#include <core/structure/Logger.h>
#include <core/utilities/RPGHelper.h>

#include "gb2rpg/def/Globals.h"


namespace fs = std::filesystem;
using namespace gb2rpg;

const static std::string INFO_NO_SWITCH_NAMES = "Could not find 'project/switch_names.txt'. Using default names for switches instead.";
const static std::string INFO_NO_VAR_NAMES = "Could not find 'project/var_names.txt'. Using default names for variables instead.";
const static std::string INFO_NO_COMMON_EVENTS = "Could not find 'project/common_events.xml'. No generated code will be added to the project.";



// public
void Database::genDatabase() {
    lcf::Database database(
        RPGMAKER::MAX_NUM_SWITCHES, RPGMAKER::MAX_NUM_VARIABLES,
        MEMORYSIZES::TOTAL_USED_ITEMS, RPGMAKER::MAX_NUM_CHARS);

    core::Logger::Get()->Log("Generating Database: RPG_RT.edb", core::LogLevel::INFO);

    genSwitches(database);
    genVariables(database);
    genItems(database);
    genCharacters(database);
    genCommonEvents(database);

    lcf::DatabaseSerializer::ToFile(GLOBALS::PROJECT::PROJECT_DIR + GLOBALS::EXPORTS::DATABASE_FILE, database);
}

void Database::genSwitches(lcf::Database& database) {
    std::ifstream nameFile(GLOBALS::PROJECT::PROJECT_DIR + GLOBALS::PROJECT::SWITCH_NAMES);
    if(!nameFile.is_open()) { 
        core::Logger::Get()->Log(INFO_NO_SWITCH_NAMES, core::LogLevel::INFO);
    }

    for(int id = RPGMAKER::MIN_ID; id < RPGMAKER::MAX_NUM_SWITCHES; ++id) {
        std::string name;
        // use supplied names
        if(nameFile.is_open()) {
            nameFile >> name;
        }
        // use default names
        else {
            name = "SW" + generateID(id);
        }

        database.addSwitch(name);
    }
}

void Database::genVariables(lcf::Database& database) {
    std::ifstream nameFile(GLOBALS::PROJECT::PROJECT_DIR + GLOBALS::PROJECT::VAR_NAMES);
    if(!nameFile.is_open()) {
        core::Logger::Get()->Log(INFO_NO_VAR_NAMES, core::LogLevel::INFO);
    }

    for(int id = RPGMAKER::MIN_ID; id < RPGMAKER::MAX_NUM_VARIABLES; ++id) {
        std::string name;
        // Use names from static variable mapping
        if (id < static_cast<int>(VARMAPPING::COUNT)) {
            name = VARMAPPING_NAMES[id];
        }
        // use supplied names
        else if (nameFile.is_open()) {
            nameFile >> name;
        }
        // use default names
        else {
            name = "VAR" + generateID(id);
        }
        
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

        database.addItem(name, static_cast<lcf::Item::ItemType>(typeID));
    }
}

void Database::genCharacters(lcf::Database& database) {
    for (int id = 1; id < RPGMAKER::MAX_NUM_CHARS; ++id) {
        std::string name = "CHAR" + generateID(id);
        database.addCharacter(name);
    }
}

void Database::genCommonEvents(lcf::Database& database) {
    std::string filePath = GLOBALS::PROJECT::PROJECT_DIR + GLOBALS::PROJECT::COMMON_EVENTS;
    if(!fs::exists({filePath})) {
        core::Logger::Get()->Log(INFO_NO_COMMON_EVENTS, core::LogLevel::INFO);
        return;
    }

    std::vector<lcf::CommonEvent> commonEvents = lcf::CommonEventSerializer::MultipleFromFile(filePath);

    database.addCommonEvents(commonEvents);
}