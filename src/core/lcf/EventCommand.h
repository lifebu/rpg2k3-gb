#pragma once

#include "Filemode.h"

#include <string>
#include <vector>

namespace tinyxml2 { class XMLDocument; }

// TODO: Does this make sense and make it easy to use the command codes?
enum CommandType {
    LABEL = 12110
};

class EventCommand {
public:
    EventCommand(std::string fileName, FILE_MODE fileMode);
    EventCommand(const EventCommand& other) = delete;
    EventCommand(EventCommand&& other) = delete;
    ~EventCommand();
    
    EventCommand& operator=(const EventCommand& other) = delete;
    EventCommand& operator=(EventCommand&& other) = delete;

private:
    tinyxml2::XMLDocument* file;
    std::string fileName;

    CommandType type;
    uint8_t indentation;
    std::string stringParameter;
    std::vector<int32_t> parameters;
};