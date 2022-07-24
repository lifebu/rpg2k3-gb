#pragma once

#include "src/core/lcf/Item.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {

class ItemSerializer {
public:
    ItemSerializer() = delete;

    static Item FromFile(std::string fileName);
    static std::unique_ptr<tinyxml2::XMLDocument> ToFile(Item& elem);
};

};