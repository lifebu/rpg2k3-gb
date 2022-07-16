#pragma once

#include <string>
#include <vector>

namespace lcf {

// TODO: Does this make sense and make it easy to use the command codes?
enum CommandType {
    LABEL = 12110
};

// TODO: Use specific command classes that inherit from the EventCommand?
// TODO: Some RPG Maker commands can be multiple event commands.
class EventCommand {
public:
    EventCommand(CommandType type, uint8_t indentation, std::string stringParameter, std::vector<int32_t> parameters);

private:
    // ~ 16bit
    CommandType type;
    uint8_t indentation;
    // can be filename ~ 240 bit
    // rarely used.
    std::string stringParameter;
    // up to 40 parameters: 1280 bit
    // more realistic: 7 parameters: 224
    // TODO: This could be made much more efficient. Most parameters do not need an entire 32-Bit range. Only control variable operands need that must can use 8 bit, or 16-bit
    // with optimization.
    // Parameters are to 50% 16 bit and 50% 8 bit
    // => even more realistic: 7 parameters @ int12: 84bit
    std::vector<int32_t> parameters;
};

};