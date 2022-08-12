#pragma once

#include "../lcf/Event.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };

namespace lcf {

class EventSerializer {
public:
    EventSerializer() = delete;

    static Event FromFile(std::string fileName);
    static std::unique_ptr<tinyxml2::XMLDocument> ToFile(Event& event);
};

};