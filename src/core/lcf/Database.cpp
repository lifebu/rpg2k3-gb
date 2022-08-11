#include "Database.h"

#include "src/core/utilities/RPGHelper.h"

namespace lcf {

void Database::addSwitch(std::string name) {
    switches.emplace_back(getNextID(switches.size()), name);
}

void Database::addVariable(std::string name) {
    variables.emplace_back(getNextID(variables.size()), name);
}

void Database::addCharacter(std::string name) {
    characters.emplace_back(getNextID(characters.size()), name);
}

void Database::addItem(std::string name, ItemType type) {
    items.emplace_back(getNextID(items.size()), name, type);
}

void Database::addCommonEvent(std::string name, TriggerType trigger) {
    commonEvents.emplace_back(getNextID(commonEvents.size()), name, trigger);
}

};