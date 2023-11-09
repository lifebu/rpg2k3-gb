#include "Database.h"

#include <algorithm>

#include "core/utilities/RPGHelper.h"

namespace lcf 
{

Database::Database(const int numOfSwitches, const int numOfVariables, const int numOfChars, const int numOfItems, const int numOfCommonEvents) 
{
    switches.reserve(numOfSwitches);
    variables.reserve(numOfVariables);
    characters.reserve(numOfChars);
    items.reserve(numOfItems);
    commonEvents.reserve(numOfCommonEvents);
}

Switch& Database::addSwitch(const std::string name) 
{
    return switches.emplace_back(getNextID(switches.size()), name);
}

void Database::addSwitch(Switch& newSwitch)
{
    switches.push_back(newSwitch);
}

Variable& Database::addVariable(const std::string name) 
{
    return variables.emplace_back(getNextID(variables.size()), name);
}

void Database::addVariable(Variable& newVariable)
{
    variables.push_back(newVariable);
}

Character& Database::addCharacter(const std::string name) 
{
    return characters.emplace_back(getNextID(characters.size()), name);
}

void Database::addCharacter(Character& newCharacter)
{
    characters.push_back(newCharacter);
}

Item& Database::addItem(const std::string name, const Item::ItemType type) 
{
    return items.emplace_back(getNextID(items.size()), name, type);
}

void Database::addItem(Item& newItem)
{
    items.push_back(newItem);
}


CommonEvent& Database::addCommonEvent(const std::string name, const CommonEvent::TriggerType trigger) 
{
    return commonEvents.emplace_back(getNextID(commonEvents.size()), name, trigger);
}

void Database::addCommonEvents(const std::vector<CommonEvent>& newCommonEvents)
{
    commonEvents.insert(commonEvents.end(), newCommonEvents.begin(), newCommonEvents.end());
}

void Database::addCommonEvent(const CommonEvent& newCommonEvent)
{
    commonEvents.push_back(newCommonEvent);
}

Item* Database::GetItemByID(uint16_t id)
{
    auto foundIt = std::find_if(items.begin(), items.end(), [id](const Item& a)
    { 
        return a.GetID() == id;
    });

    if(foundIt != items.end())
    {
        return &(*foundIt);
    }

    return nullptr;
}

Character* Database::GetCharacterByID(uint16_t id)
{
    auto foundIt = std::find_if(characters.begin(), characters.end(), [id](const Character& a)
    { 
        return a.id == id;
    });
    
    if(foundIt != characters.end())
    {
        return &(*foundIt);
    }

    return nullptr;
}
};