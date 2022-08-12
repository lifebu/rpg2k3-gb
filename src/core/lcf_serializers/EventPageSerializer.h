#pragma once

#include "../lcf/EventPage.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };

namespace lcf {

class EventPageSerializer {
public:
    EventPageSerializer() = delete;

    static EventPage FromFile(std::string fileName);
    static std::unique_ptr<tinyxml2::XMLDocument> ToFile(EventPage& eventPage);
};

};