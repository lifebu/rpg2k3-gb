#pragma once

#include "Filemode.h"

#include <string>
#include <vector>

namespace tinyxml2 { class XMLDocument; }
class EventCommand;

class EventPage {
public:
    EventPage(std::string fileName, FILE_MODE fileMode);
    EventPage(const EventPage& other) = delete;
    EventPage(EventPage&& other) = delete;
    ~EventPage();
    
    EventPage& operator=(const EventPage& other) = delete;
    EventPage& operator=(EventPage&& other) = delete;

private:
    tinyxml2::XMLDocument* file;
    std::string fileName;

    uint16_t id;
    std::vector<EventCommand> eventCommands;
};