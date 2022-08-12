#include "EventSerializer.h"

#include "Templates.h"
#include "EventPageSerializer.h"

#include "src/core/utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>

namespace lcf {

Event EventSerializer::FromFile(std::string fileName) {
    // TODO: Implement!
    return Event(1, "", 0, 0);
}

std::unique_ptr<tinyxml2::XMLDocument> EventSerializer::ToFile(Event& event) {
    auto eventTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::EVENT);

    // Set Event ID
    eventTempl->RootElement()->SetAttribute("id", generateID(event.id).c_str());

    // Set Event Name
    auto* nameElem = eventTempl->TraverseElement("//name")->FirstChild();
    nameElem->SetValue((event.name).c_str());

    // Set Event Coordinates
    auto* xCoord = eventTempl->TraverseElement("//x")->FirstChild();
    xCoord->SetValue(std::to_string(event.x).c_str());

    auto* yCoord = eventTempl->TraverseElement("//y")->FirstChild();
    yCoord->SetValue(std::to_string(event.y).c_str());

    // Insert Event Pages
    for(auto& eventPage : event.eventPages) {
        auto eventPageDoc = EventPageSerializer::ToFile(eventPage);

        eventPageDoc->DeepCloneInsertBack(eventTempl.get(), eventTempl->TraverseElement("//event_commands"));
    }

    return eventTempl;
}

};
