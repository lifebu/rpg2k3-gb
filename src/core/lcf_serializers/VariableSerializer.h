#pragma once

#include "src/core/lcf/Variable.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {

class VariableSerializer {
public:
    VariableSerializer() = delete;

    static Variable FromFile(std::string fileName);
    static std::unique_ptr<tinyxml2::XMLDocument> ToFile(Variable& elem);
};

};