#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "core/lcf/event/EventCommand.h"

namespace lcf 
{

class CommonEvent 
{
    friend class CommonEventSerializer;

public:
    enum TriggerType 
    {
        AUTORUN = 3,
        PARALLEL_PROCESS = 4,
        NONE = 5
    };

    CommonEvent(const uint16_t id, const std::string name, const TriggerType trigger);
    CommonEvent(const uint16_t id, const std::string name, const TriggerType trigger, const size_t numOfEventCommands);

    void addEventCommand(EventCommand& other);

private:
    uint16_t id;
    std::string name;
    TriggerType trigger;
    std::vector<EventCommand> eventCommands;
};

};