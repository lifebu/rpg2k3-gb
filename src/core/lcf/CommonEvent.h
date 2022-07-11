#pragma once

#include "Filemode.h"

#include <string>
#include <vector>

namespace tinyxml2 { class XMLDocument; }
class EventCommand;

class CommonEvent {
public:
    CommonEvent(std::string fileName, FILE_MODE fileMode);
    CommonEvent(const CommonEvent& other) = delete;
    CommonEvent(CommonEvent&& other) = delete;
    ~CommonEvent();
    
    CommonEvent& operator=(const CommonEvent& other) = delete;
    CommonEvent& operator=(CommonEvent&& other) = delete;

    std::string getName();
    void setName(std::string val);

    bool getUseConditionSwitch();
    void setUseConditionSwitch(bool val);

    uint16_t getConditionSwitchID();
    void setConditionSwitchID(uint16_t val);

    void addEventCommand(EventCommand& eventCommand);

private:
    tinyxml2::XMLDocument* file;
    std::string fileName;

    std::string name;
    bool useConditionSwitch;
    uint16_t conditionSwitchID;
    std::vector<EventCommand> eventCommands;
};