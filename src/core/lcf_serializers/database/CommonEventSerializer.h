#pragma once

#include "../../lcf_serializers/serializer_types/PartialSerializer.h"
#include "../../lcf_serializers/serializer_types/MultiSerializer.h"
#include "lcf/database/CommonEvent.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {

class CommonEventSerializer : PartialSerializer<CommonEvent>, MultiSerializer<CommonEvent> {
public:
    CommonEventSerializer();

    // PartialSerializer
    CommonEvent FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) override;
    std::unique_ptr<tinyxml2::XMLDocument> ToFile(CommonEvent& elem) override;

    // MultiSerializer
    std::vector<CommonEvent> MultipleFromFile(std::string fileName) override;
    void MultipleToFile(std::string fileName, std::vector<CommonEvent>& elems) override;
};

};