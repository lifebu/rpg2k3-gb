#pragma once

#include "../../lcf_serializers/serializer_types/PartialSerializer.h"
#include "lcf/database/Item.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {

class ItemSerializer : PartialSerializer<Item> {
public:
    ItemSerializer();

    Item FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) override;
    std::unique_ptr<tinyxml2::XMLDocument> ToFile(Item& elem) override;
};

};