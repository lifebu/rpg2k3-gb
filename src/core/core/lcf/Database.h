#pragma once

#include <string>

#include "core/lcf/database/LCFType.h"
#include "core/lcf/database/Character.h"
#include "core/lcf/database/Item.h"
#include "core/lcf/database/CommonEvent.h"
#include "core/lcf/event/EventCommand.h"

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

    Item* GetItemByID(uint16_t id);
    Character* GetCharacterByID(uint16_t id);

private:
    std::vector<Switch> switches;
    std::vector<Variable> variables;
    std::vector<Character> characters;
    std::vector<Item> items;
    std::vector<CommonEvent> commonEvents;
};

};