#pragma once

#include "EventPage.h"

#include <string>
#include <vector>


namespace lcf {

class Event {
    friend class EventSerializer;

public:
    Event(const uint16_t id, const std::string name, const uint16_t x, const uint16_t y);

    EventPage& addEventPage();

public:
    uint16_t x;
    uint16_t y;
private:
    const uint16_t id;
    const std::string name;
    std::vector<EventPage> eventPages;
};

};