#include "MapSerializer.h"

#include "Templates.h"

#include "EventCommandSerializer.h"

#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>

namespace lcf 
{

Map MapSerializer::FromFile(std::string fileName) 
{
    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) 
    {
        std::cout << file.ErrorStr() << std::endl;
        return Map(0);
    }

    Map map = Map(0);

    auto* currentMapEvent = file.TraverseElement("/LMU/Map/events/Event");
    while(currentMapEvent)
    {
        Event newEvent = EventFromFileImpl(currentMapEvent);
        map.addEvent(newEvent);
        currentMapEvent = currentMapEvent->NextSiblingElement();
    }

    return map;
}

void MapSerializer::ToFile(std::string fileName, Map& map) 
{
    tinyxml2::XMLDocument mapTempl(TEMPLATES::MAP);
    tinyxml2::XMLDocument eventTempl(TEMPLATES::EVENT);

    // Insert map infos in to the maptree.
    for(auto& event : map.events) 
    {
        auto* eventElement = eventTempl.TraverseElement("/Event");
        EventToFileImpl(event, &mapTempl, eventElement);

        eventElement->DeepCloneInsertBack(&mapTempl, mapTempl.TraverseElement("/LMU/Map/events"));
    }

    mapTempl.SaveFile(fileName.c_str(), false);
    if (mapTempl.Error()) 
    {
        std::cout << mapTempl.ErrorStr() << std::endl;
    }
}

Event MapSerializer::EventFromFileImpl(tinyxml2::XMLElement* eventElem)
{
    // Get Event ID
    uint16_t id = eventElem->IntAttribute("id");

    // Get Event Name.
    auto* nameElem = eventElem->TraverseElement("/name")->FirstChild()->ToText();
    std::string name = (nameElem == nullptr) ? "" : nameElem->Value();

    // Get Event Coordinates
    auto* xCoordElem = eventElem->TraverseElement("/x")->FirstChild();
    uint16_t x = std::stoi(xCoordElem->Value());

    auto* yCoordElem = eventElem->TraverseElement("/y")->FirstChild();
    uint16_t y = std::stoi(yCoordElem->Value());

    Event newEvent = Event(id, name, x, y);
    auto* currentPage = eventElem->TraverseElement("/pages");
    while(currentPage)
    {
        EventPage newEventPage = EventPageFromFileImpl(currentPage);
        newEvent.addEventPage(newEventPage);
        currentPage = currentPage->NextSiblingElement();
    }

    return newEvent;
}

void MapSerializer::EventToFileImpl(const Event& elem, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* eventElem)
{
    tinyxml2::XMLDocument eventPageTempl(TEMPLATES::EVENT_PAGE);

    // Set Event ID
    eventElem->SetAttribute("id", generateID(elem.id).c_str());

    // Set Event Name
    auto* nameElem = eventElem->TraverseElement("/name")->FirstChild()->ToText();
    nameElem->SetValue(elem.name.c_str());

    // Set Event Coordinates
    auto* xCoordElem = eventElem->TraverseElement("/x")->FirstChild();
    xCoordElem->SetValue(std::to_string(elem.x).c_str());
    
    auto* yCoordElem = eventElem->TraverseElement("/y")->FirstChild();
    yCoordElem->SetValue(std::to_string(elem.y).c_str());

    // Insert Event Pages
    for(auto& eventPage : elem.eventPages) 
    {
        auto* eventPageElement = eventPageTempl.TraverseElement("/EventPage");
        EventPageToFileImpl(eventPage, doc, eventPageElement);

        eventPageElement->DeepCloneInsertBack(doc, eventElem->TraverseElement("/pages"));
    }
}

EventPage MapSerializer::EventPageFromFileImpl(tinyxml2::XMLElement* eventPageElem)
{
    // Get Event ID
    uint16_t id = eventPageElem->IntAttribute("id");

    // Get EventCommands
    EventPage newEventPage = EventPage(id);
    auto* currentEventCommand = eventPageElem->TraverseElement("/event_commands");
    while(currentEventCommand)
    {
        EventCommand newEventCommands = EventCommandSerializer::FromFileImpl(currentEventCommand);
        newEventPage.addEventCommand(newEventCommands);

        currentEventCommand = currentEventCommand->NextSiblingElement();
    }

    return newEventPage;
}

void MapSerializer::EventPageToFileImpl(const EventPage& elem, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* eventPageElem)
{
    tinyxml2::XMLDocument eventCommandTempl(TEMPLATES::EVENT_COMMAND);

    // Set Event ID
    eventPageElem->SetAttribute("id", generateID(elem.id).c_str());

    // Add Event Commands
    for(auto& eventCommand : elem.eventCommands) 
    {
        auto* eventCommandElem = eventCommandTempl.TraverseElement("/EventCommand");
        EventCommandSerializer::ToFileImpl(eventCommand, eventCommandElem);

        eventCommandElem->DeepCloneInsertBack(doc, eventPageElem->TraverseElement("/event_commands"));
    }
}

};
