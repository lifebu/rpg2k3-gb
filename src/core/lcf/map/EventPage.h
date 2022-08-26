#pragma once

#include "../common/EventCommand.h"

#include <string>
#include <vector>


namespace lcf {

class EventCommand;

class EventPage {
    friend class EventPageSerializer;

public:
    EventPage(const uint16_t id);

    void addEventCommands(const std::vector<EventCommand>& commands);

private:
    const uint16_t id;
    std::vector<EventCommand> eventCommands;
};

};