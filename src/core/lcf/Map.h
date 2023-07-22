#pragma once

#include "map/Event.h"

#include <string>
#include <vector>

namespace tinyxml2 { class XMLDocument; }

namespace lcf 
{

class Map 
{
    friend class MapSerializer;
    friend class MapSerializerRAPID;

public:
    Map(const int numOfEvents = 0);

    Event& addEvent(const std::string name, const uint16_t x, const uint16_t y);
    void addEvent(Event& other);

    const uint16_t nextEventID();

    Event* GetEventByID(uint16_t id);
    Event* GetEventByPosition(uint16_t x, uint16_t y);
    

private:
    std::vector<Event> events;
};

};