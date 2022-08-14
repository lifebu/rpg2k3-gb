#pragma once

#include "../../lcf/common/EventCommand.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {

class EventCommandSerializer {
public:
    EventCommandSerializer() = delete;

    static EventCommand FromFile(std::string fileName);
    static std::unique_ptr<tinyxml2::XMLDocument> ToFile(EventCommand& elem);

    static std::vector<EventCommand> MultipleFromFile(std::string fileName);
};

};