#pragma once

#include "lcf/database/CommonEvent.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {

class CommonEventSerializer {
public:
    CommonEventSerializer() = delete;

    static CommonEvent FromFile(std::string fileName);
    static std::unique_ptr<tinyxml2::XMLDocument> ToFile(CommonEvent& elem);
};

};