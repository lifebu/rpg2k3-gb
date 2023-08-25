#include "Map.h"

#include <iostream>
#include <algorithm>

#include "core/utilities/RPGHelper.h"

namespace lcf 
{

Map::Map(const int numOfEvents) 
{
    events.reserve(numOfEvents);
}

Event& Map::addEvent(const std::string name, const uint16_t x, const uint16_t y) 
{
    return events.emplace_back(getNextID(events.size()), name, x, y);
}

void Map::addEvent(Event& other)
{
    events.push_back(other);
}

const uint16_t Map::nextEventID() 
{
    return getNextID(events.size());
}

Event* Map::GetEventByID(uint16_t id)
{
    auto foundIt = std::find_if(events.begin(), events.end(), [id](const Event& a)
    { 
        return a.GetID() == id;
    });

    if(foundIt != events.end())
    {
        return &(*foundIt);
    }

    return nullptr;
}

Event* Map::GetEventByPosition(uint16_t x, uint16_t y)
{
    auto foundIt = std::find_if(events.begin(), events.end(), [x, y](const Event& a)
    { 
        return a.x == x && a.y == y;
    });

    if(foundIt != events.end())
    {
        return &(*foundIt);
    }

    return nullptr;
}
}