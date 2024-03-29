#pragma once

#include <string>
#include <vector>

#include "EventPage.h"

namespace lcf 
{

class Event 
{
    friend class MapSerializer;
    friend class MapSerializerRAPID;

public:
    Event(const uint16_t id, const std::string name, const uint16_t x, const uint16_t y);

    EventPage& addEventPage();
    void addEventPage(EventPage& other);

    uint16_t GetID() const;
    std::string GetEventName() const;
    EventPage* GetEventPageByID(uint16_t id);

public:
    uint16_t x;
    uint16_t y;

private:
    uint16_t id;
    std::string name;
    std::vector<EventPage> eventPages;
};

};