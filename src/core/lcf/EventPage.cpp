#include "EventPage.h"

#include <cassert>

#include "src/core/utilities/RPGHelper.h"

namespace lcf {

// public
EventPage::EventPage(uint16_t id) :id(id) {
    assert(1 <= id < RPGMAKER::MAX_PAGES_PER_EVENT);
}

void EventPage::addEventCommands(std::vector<EventCommand>& commands) {
    eventCommands.insert(eventCommands.end(), commands.begin(), commands.end());
}

};