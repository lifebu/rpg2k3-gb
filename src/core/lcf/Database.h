#pragma once

#include "LCFType.h"
#include "Character.h"
#include "Item.h"
#include "CommonEvent.h"
#include "EventCommand.h"

#include <string>


namespace lcf {

class Database {
    friend class DatabaseSerializer;

public: 
    void addSwitch(std::string name);
    void addVariable(std::string name);
    void addCharacter(std::string name);
    void addItem(std::string name, ItemType type);
    void addCommonEvent(std::string name, TriggerType trigger);

private:
    std::vector<Switch> switches;
    std::vector<Variable> variables;
    std::vector<Character> characters;
    std::vector<Item> items;
    std::vector<CommonEvent> commonEvents;
};

};