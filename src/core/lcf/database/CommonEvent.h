#pragma once

#include <string>
#include <vector>


namespace lcf {


class EventCommand;

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
    const uint16_t id;
    const std::string name;
    const TriggerType trigger;
    std::vector<EventCommand> eventCommands;
};

};