#pragma once

#include <string>
#include <vector>


namespace lcf {

// TODO: Does this make sense and make it easy to use the command codes?
enum CommandType {
    LABEL = 12110,
    END_EVENT_PROCESSING = 12310
};

// TODO: Use specific command classes that inherit from the EventCommand?
// TODO: Some RPG Maker commands can be multiple event commands.
class EventCommand {
    // TODO: Not that nice!
    friend class EventCommandSerializer;

public:
    EventCommand(CommandType type, uint8_t indentation, std::string stringParam, std::vector<int32_t> parameters);

    // TODO: Not a big fan of simple setter if they don't do anything. Do I need them?
    void setParameters(std::vector<int32_t> parameters);
    void setType(CommandType type);

private:
    // ~ 16bit
    CommandType type;
    uint8_t indentation;
    // ~ 240 bit, rarely used
    std::string stringParam;
    // ~ 7 parameters @ int12: 84bit
    std::vector<int32_t> parameters;
};

};