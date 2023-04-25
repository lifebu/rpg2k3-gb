#include "EventPageSerializer.h"

#include "lcf_serializers/Templates.h"
#include "lcf_serializers/EventCommandSerializer.h"

#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>

namespace lcf {

EventPageSerializer::EventPageSerializer() {}

EventPage EventPageSerializer::FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) {
    return EventPage(1);
}

std::unique_ptr<tinyxml2::XMLDocument> EventPageSerializer::ToFile(EventPage& eventPage) {
    auto eventPageTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::EVENT_PAGE);

    // Set Eventpage ID
    eventPageTempl->RootElement()->SetAttribute("id", generateID(eventPage.id).c_str());

    // Insert Event Commands
    for(auto& eventCommand : eventPage.eventCommands) {
        auto eventCommandDoc = EventCommandSerializer().ToFile(eventCommand);

        eventCommandDoc->DeepCloneInsertBack(eventPageTempl.get(), eventPageTempl->TraverseElement("//event_commands"));
    }

    return eventPageTempl;
}

};
