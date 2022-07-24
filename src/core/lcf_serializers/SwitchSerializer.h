#pragma once

#include "src/core/lcf/Switch.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {

class SwitchSerializer {
public:
    SwitchSerializer() = delete;

    static Switch FromFile(std::string fileName);
    static std::unique_ptr<tinyxml2::XMLDocument> ToFile(Switch& elem);
};

};