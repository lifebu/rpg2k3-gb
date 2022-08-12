#include "Event.h"

#include <cassert>

#include "src/core/utilities/RPGHelper.h"

namespace lcf {

// public
Event::Event(uint16_t id, std::string name, uint16_t x, uint16_t y) :
    id(id), name(name), x(x), y(y) {
    assert(1 <= id < MEMORYSIZES::MAX_PAGES_PER_EVENT);
}

};