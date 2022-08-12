#pragma once

#include "EventPage.h"

#include <string>
#include <vector>


namespace lcf {

class Event {
    friend class EventSerializer;
public:
    Event(uint16_t id, std::string name, uint16_t x, uint16_t y);

    void addEventPage();

private:
    uint16_t id;
    std::string name;
    uint16_t x;
    uint16_t y;
    std::vector<EventPage> eventPages;
};

};