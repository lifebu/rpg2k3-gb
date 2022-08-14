#pragma once

#include "../../lcf_serializers/serializer_types/PartialSerializer.h"
#include "../../lcf_serializers/serializer_types/MultiSerializer.h"
#include "../../lcf/common/EventCommand.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {

class EventCommandSerializer : PartialSerializer<EventCommand>, MultiSerializer<EventCommand> {
public:
    EventCommandSerializer();

    // PartialSerializer
    EventCommand FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) override;
    std::unique_ptr<tinyxml2::XMLDocument> ToFile(EventCommand& elem) override;

    // MultiSerializer
    std::vector<EventCommand> MultipleFromFile(std::string fileName) override;
    void MultipleToFile(std::string fileName, std::vector<EventCommand>& elems) override;
};

};