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
    
    // Insert map infos in to the maptree.
    for(auto& event : map.events) 
    {
        // TODO: This does not feel great but greatly reduces memory (because otherwise each iteration influences each other)
        // TODO: Maybe make a copy of template every iteration?
        tinyxml2::XMLDocument eventTempl(TEMPLATES::EVENT);

        auto* eventElement = eventTempl.TraverseElement("/Event");
        EventToFileImpl(event, &eventTempl, eventElement);

        eventElement->DeepCloneInsertBack(&mapTempl, mapTempl.TraverseElement("/LMU/Map/events"));
    }

    // TODO: compact could be an argument?
    bool compactMode = false;
    mapTempl.SaveFile(fileName.c_str(), compactMode);
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
    auto* currentPage = eventElem->TraverseElement("/pages/EventPage");
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
        // TODO: This does not feel great but greatly reduces memory (because otherwise each iteration influences each other)
        // TODO: I may need something to cut the pages of the eventElem away before generation? (delete every child in /pages) at the start of this function?
        // TODO: Maybe make a copy of template every iteration?
        tinyxml2::XMLDocument eventPageTempl(TEMPLATES::EVENT_PAGE);
        auto* eventPageElement = eventPageTempl.TraverseElement("/EventPage");
        EventPageToFileImpl(eventPage, &eventPageTempl, eventPageElement);


        eventPageElement->DeepCloneInsertBack(doc, eventElem->TraverseElement("/pages"));
    }
}

EventPage MapSerializer::EventPageFromFileImpl(tinyxml2::XMLElement* eventPageElem)
{
    // Get Event ID
    uint16_t id = eventPageElem->IntAttribute("id");

    // Get EventCommands
    EventPage newEventPage = EventPage(id);
    auto* currentEventCommand = eventPageElem->TraverseElement("/event_commands/EventCommand");
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
    // Set Event ID
    eventPageElem->SetAttribute("id", generateID(elem.id).c_str());

    int a = elem.eventCommands.size();
    // Add Event Commands
    for(auto& eventCommand : elem.eventCommands) 
    {
        // TODO: This does not feel great but greatly reduces memory (because otherwise each iteration influences each other)
        // TODO: I may need something to cut the commands of the eventPageElem away before generation? (delete every child in /event_commands) at the start of this function?
        // TODO: Maybe make a copy of template every iteration?
        tinyxml2::XMLDocument eventCommandTempl(TEMPLATES::EVENT_COMMAND);

        auto* eventCommandElem = eventCommandTempl.TraverseElement("/EventCommand");
        EventCommandSerializer::ToFileImpl(eventCommand, eventCommandElem);

        eventCommandElem->DeepCloneInsertBack(doc, eventPageElem->TraverseElement("/event_commands"));
    }
}

};
