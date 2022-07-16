#pragma once

#include "Filemode.h"

#include <string>
#include <vector>

namespace tinyxml2 { class XMLDocument; }
class EventPage;

class Event {
public:
    Event(std::string fileName, FILE_MODE fileMode);
    Event(const Event& other) = delete;
    Event(Event&& other) = delete;
    ~Event();
    
    Event& operator=(const Event& other) = delete;
    Event& operator=(Event&& other) = delete;

private:
    tinyxml2::XMLDocument* file;
    std::string fileName;

    uint16_t id;
    std::string name;
    uint16_t x;
    uint16_t y;
    std::vector<EventPage> eventPages;
};