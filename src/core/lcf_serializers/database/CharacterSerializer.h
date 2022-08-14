#pragma once

#include "lcf/database/Character.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {

class CharacterSerializer {
public:
    CharacterSerializer() = delete;

    static Character FromFile(std::string fileName);
    static std::unique_ptr<tinyxml2::XMLDocument> ToFile(Character& elem);
};

};