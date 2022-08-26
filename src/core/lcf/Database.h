#pragma once

#include "database/LCFType.h"
#include "database/Character.h"
#include "database/Item.h"
#include "database/CommonEvent.h"
#include "common/EventCommand.h"

#include <string>


namespace lcf {

class Database {
    friend class DatabaseSerializer;

public: 
    Database(const int numOfSwitches = 0, const int numOfVariables = 0, const int numOfChars = 0, const int numOfItems = 0, const int numOfCommonEvents = 0);

    Switch& addSwitch(const std::string name);
    Variable& addVariable(const std::string name);
    Character& addCharacter(const std::string name);
    Item& addItem(const std::string name, const Item::ItemType type);
    CommonEvent& addCommonEvent(const std::string name, const CommonEvent::TriggerType trigger);

private:
    std::vector<Switch> switches;
    std::vector<Variable> variables;
    std::vector<Character> characters;
    std::vector<Item> items;
    std::vector<CommonEvent> commonEvents;
};

};