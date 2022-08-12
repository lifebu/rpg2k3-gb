#pragma once

#include "EventCommand.h"

#include <string>
#include <vector>


namespace lcf {

class EventCommand;

class EventPage {
    friend class EventPageSerializer;
public:
    EventPage(uint16_t id);

    void addEventCommands(std::vector<EventCommand>& commands);

private:
    uint16_t id;
    std::vector<EventCommand> eventCommands;
};

};