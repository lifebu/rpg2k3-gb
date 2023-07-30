#include "Event.h"

#include <algorithm>
#include <cassert>

#include "utilities/RPGHelper.h"

namespace lcf {

// public
Event::Event(const uint16_t id, const std::string name, const uint16_t x, const uint16_t y) :
    id(id), name(name), x(x), y(y) 
{
    assert(1 <= id < RPGMAKER::MAX_PAGES_PER_EVENT);
}

EventPage& Event::addEventPage() 
{
    return eventPages.emplace_back(getNextID(eventPages.size()));
}

void Event::addEventPage(EventPage& other)
{
    eventPages.push_back(other);
}

uint16_t Event::GetID() const
{ 
    return id; 
}

std::string Event::GetEventName() const
{
    return name;
}

EventPage* Event::GetEventPageByID(uint16_t id)
{
    auto foundIt = std::find_if(eventPages.begin(), eventPages.end(), [id](const EventPage& a)
    { 
        return a.GetID() == id;
    });

    if(foundIt != eventPages.end())
    {
        return &(*foundIt);
    }

    return nullptr;
}
};