#include "EventPage.h"

#include <cassert>

#include "utilities/RPGHelper.h"

namespace lcf 
{

// public
EventPage::EventPage(const uint16_t id) :id(id) 
{
    assert(1 <= id < RPGMAKER::MAX_PAGES_PER_EVENT);
}

void EventPage::addEventCommands(const std::vector<EventCommand>& commands) 
{
    eventCommands.insert(eventCommands.end(), commands.begin(), commands.end());
}

void EventPage::addEventCommand(const EventCommand& command)
{
    eventCommands.push_back(command);
}

uint16_t EventPage::GetID() const
{ 
    return id;
}

EventCommand* EventPage::GetEventCommandByIndex(uint32_t index)
{
    if(index >= eventCommands.size())
    {
        return nullptr;
    }
    return &eventCommands.at(index);
}
};