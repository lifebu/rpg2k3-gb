#pragma once

#include "../../lcf_serializers/serializer_types/PartialSerializer.h"
#include "lcf/map/EventPage.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };

namespace lcf {

class EventPageSerializer : PartialSerializer<EventPage> {
public:
    EventPageSerializer();

    EventPage FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) override;
    std::unique_ptr<tinyxml2::XMLDocument> ToFile(EventPage& eventPage) override;
};

};