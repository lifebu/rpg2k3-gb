#include "Database.h"

#include "utilities/RPGHelper.h"

namespace lcf {

Database::Database(const int numOfSwitches, const int numOfVariables, const int numOfChars, const int numOfItems, const int numOfCommonEvents) {
    switches.reserve(numOfSwitches);
    variables.reserve(numOfVariables);
    characters.reserve(numOfChars);
    items.reserve(numOfItems);
    commonEvents.reserve(numOfCommonEvents);
}

Switch& Database::addSwitch(const std::string name) {
    return switches.emplace_back(getNextID(switches.size()), name);
}

Variable& Database::addVariable(const std::string name) {
    return variables.emplace_back(getNextID(variables.size()), name);
}

Character& Database::addCharacter(const std::string name) {
    return characters.emplace_back(getNextID(characters.size()), name);
}

Item& Database::addItem(const std::string name, const Item::ItemType type) {
    return items.emplace_back(getNextID(items.size()), name, type);
}

CommonEvent& Database::addCommonEvent(const std::string name, const CommonEvent::TriggerType trigger) {
    return commonEvents.emplace_back(getNextID(commonEvents.size()), name, trigger);
}

};