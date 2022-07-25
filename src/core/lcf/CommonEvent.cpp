#include "CommonEvent.h"

#include "EventCommand.h"
#include "src/core/utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"


namespace lcf {

// public
CommonEvent::CommonEvent(uint16_t id, std::string name, TriggerType trigger) {

    setID(id);
    setName(name);
    setTriggerType(trigger);
}

std::string CommonEvent::getName() {
    return name;
}
void CommonEvent::setName(std::string val) {
    name = val;
}

TriggerType CommonEvent::getTriggerType() {
    return trigger;
}

void CommonEvent::setTriggerType(TriggerType val) {
    trigger = val;
}

void CommonEvent::addEventCommand(EventCommand&& eventCommand) {
    eventCommands.emplace_back(eventCommand);
}

};