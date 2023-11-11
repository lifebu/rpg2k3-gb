#include "CommonEvent.h"

#include "core/pch.h"

#include "core/def/RPGMaker.h"
#include "core/lcf/event/EventCommand.h"

namespace lcf 
{

// public
CommonEvent::CommonEvent(const uint16_t id, const std::string name, 
    const TriggerType trigger) : 
        id(id), name(name), trigger(trigger) 
{
    assert(1 <= id < RPGMAKER::MAX_ID);
}

CommonEvent::CommonEvent(const uint16_t id, const std::string name, 
    const TriggerType trigger, const size_t numOfEventCommands) : 
        id(id), name(name), trigger(trigger) 
{
    eventCommands.reserve(numOfEventCommands);
}

void CommonEvent::addEventCommand(EventCommand& other)
{
    eventCommands.push_back(other);
}
};