#include "EventPage.h"

#include <cassert>

#include "utilities/RPGHelper.h"

namespace lcf {

// public
EventPage::EventPage(const uint16_t id) :id(id) {
    assert(1 <= id < RPGMAKER::MAX_PAGES_PER_EVENT);
}

void EventPage::addEventCommands(const std::vector<EventCommand>& commands) {
    eventCommands.insert(eventCommands.end(), commands.begin(), commands.end());
}

};