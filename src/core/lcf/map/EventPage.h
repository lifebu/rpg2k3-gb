#pragma once

#include "../event/EventCommand.h"

#include <string>
#include <vector>


namespace lcf {

class EventCommand;

class EventPage {
    friend class MapSerializer;
    friend class MapSerializerRAPID;

public:
    EventPage(const uint16_t id);

    void addEventCommands(const std::vector<EventCommand>& commands);
    void addEventCommand(const EventCommand& command);

    uint16_t GetID() const;
    EventCommand* GetEventCommandByIndex(uint32_t index);

private:
    const uint16_t id;
    std::vector<EventCommand> eventCommands;
};

};