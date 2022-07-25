#pragma once

#include "src/core/lcf/EventCommand.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {

class EventCommandSerializer {
public:
    EventCommandSerializer() = delete;

    static EventCommand FromFile(std::string fileName);
    static std::unique_ptr<tinyxml2::XMLDocument> ToFile(EventCommand& elem);
};

};