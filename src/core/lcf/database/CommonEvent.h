#pragma once

#include <string>
#include <vector>


namespace lcf {

enum TriggerType {
    AUTORUN = 3,
    PARALLEL_PROCESS = 4,
    NONE = 5
};

class EventCommand;

class CommonEvent {
    // TODO: Not that nice!
    friend class CommonEventSerializer;

public:
    CommonEvent(uint16_t id, std::string name, TriggerType trigger);

    uint16_t getID();
    void setID(uint16_t val);

    std::string getName();
    void setName(std::string val);

    TriggerType getTriggerType();
    void setTriggerType(TriggerType val);

    void addEventCommand(EventCommand&& eventCommand);

private:
    uint16_t id;
    std::string name;
    TriggerType trigger;
    std::vector<EventCommand> eventCommands;
};

};