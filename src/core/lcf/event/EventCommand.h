#pragma once

#include <string>
#include <vector>
#include <cstdint>


namespace lcf {

class EventCommand {
    friend class EventCommandSerializer;
    friend class EventCommandSerializerRAPID;
    friend class EventCommandFactory;

public:
    enum CommandType 
    {
        NO_OP = 10,
        FIRST_LINE_SHOW_TEXT = 10110,
        MULTI_LINE_SHOW_TEXT = 20110,
        CONDITIONAL_BRANCH = 12010,
        ELSE_BRANCH = 22010,
        END_BRANCH = 22011,
        CHOICES = 10140,
        CHOICE_CASE = 20140,
        CHOICE_BRANCH_END = 20141,
        INPUT_NUMBER = 10150,
        CONTROL_VARIABLE = 10220,
        LABEL = 12110,
        JUMP_TO_LABEL = 12120,
        END_EVENT_PROCESSING = 12310,
        FIRST_LINE_COMMENT = 12410,
        MULTI_LINE_COMMENT = 22410

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
    uint8_t indentation = 0;
};

};