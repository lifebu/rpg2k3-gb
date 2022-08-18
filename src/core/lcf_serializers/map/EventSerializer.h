#pragma once

#include "../../lcf_serializers/serializer_types/PartialSerializer.h"
#include "lcf/map/Event.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };

namespace lcf {

class EventSerializer : PartialSerializer<Event> {
public:
    EventSerializer();

    Event FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) override;
    std::unique_ptr<tinyxml2::XMLDocument> ToFile(Event& event) override;
};

};