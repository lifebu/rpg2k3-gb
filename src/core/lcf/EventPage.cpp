#include "EventPage.h"

#include <cassert>

#include "src/core/utilities/RPGHelper.h"

namespace lcf {

// public
EventPage::EventPage(uint16_t id) {
    assert(1 <= id < MEMORYSIZES::MAX_PAGES_PER_EVENT);
    this->id = id;
}

};