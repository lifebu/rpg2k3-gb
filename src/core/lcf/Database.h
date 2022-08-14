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