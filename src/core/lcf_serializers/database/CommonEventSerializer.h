#pragma once

#include "../../lcf_serializers/serializer_types/PartialSerializer.h"
#include "lcf/database/CommonEvent.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {

class CommonEventSerializer : PartialSerializer<CommonEvent> {
public:
    CommonEventSerializer();

    CommonEvent FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) override;
    std::unique_ptr<tinyxml2::XMLDocument> ToFile(CommonEvent& elem) override;
};

};