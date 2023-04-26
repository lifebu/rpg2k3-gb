#pragma once

#include "database/LCFType.h"
#include "database/Character.h"
#include "database/Item.h"
#include "database/CommonEvent.h"
#include "event/EventCommand.h"

#include <string>


namespace lcf {

class Database {
    friend class DatabaseSerializer;

public: 
    Database(const int numOfSwitches = 0, const int numOfVariables = 0, const int numOfChars = 0, const int numOfItems = 0, const int numOfCommonEvents = 0);

    Switch& addSwitch(const std::string name);
    void addSwitch(Switch& newSwitch);

    Variable& addVariable(const std::string name);
    void addVariable(Variable& newVariable);

    Character& addCharacter(const std::string name);
    void addCharacter(Character& newCharacter);

    Item& addItem(const std::string name, const Item::ItemType type);
    void addItem(Item& newItem);

    CommonEvent& addCommonEvent(const std::string name, const CommonEvent::TriggerType trigger);
    void addCommonEvents(const std::vector<CommonEvent>& newCommonEvents);
    void addCommonEvent(const CommonEvent& command);

private:
    std::vector<Switch> switches;
    std::vector<Variable> variables;
    std::vector<Character> characters;
    std::vector<Item> items;
    std::vector<CommonEvent> commonEvents;
};

};