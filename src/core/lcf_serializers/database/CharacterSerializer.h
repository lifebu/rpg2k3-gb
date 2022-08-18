#pragma once

#include "../../lcf_serializers/serializer_types/PartialSerializer.h"
#include "lcf/database/Character.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {

class CharacterSerializer : PartialSerializer<Character> {
public:
    CharacterSerializer();

    Character FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) override;
    std::unique_ptr<tinyxml2::XMLDocument> ToFile(Character& elem) override;
};

};