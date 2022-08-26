#pragma once

#include <string>
#include <vector>


namespace lcf {



// TODO: Still need a good way to manage and create EventCommands, good enough for now.
class EventCommand {
    friend class EventCommandSerializer;

public:
    enum CommandType {
        LABEL = 12110,
        END_EVENT_PROCESSING = 12310
    };

    EventCommand(const CommandType type, const uint8_t indentation, const std::string stringParam, const std::vector<int32_t> parameters);


    // ~ 16bit
    CommandType type;
    // ~ 240 bit, rarely used
    std::string stringParam;
    // ~ 7 parameters @ int12: 84bit
    std::vector<int32_t> parameters;
private:
    // TODO: should create a system to automatically manage indentation.
    uint8_t indentation;
};

};