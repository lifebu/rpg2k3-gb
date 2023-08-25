#include "MapSerializer.h"

#include <tinyxml2/tinyxml2.h>

#include "core/lcf_serializers/Templates.h"
#include "core/lcf_serializers/EventCommandSerializer.h"
#include "core/structure/Logger.h"
#include "core/utilities/RPGHelper.h"

namespace lcf 
{

std::unique_ptr<tinyxml2::XMLDocument> MapSerializer::mapTempl;
std::unique_ptr<tinyxml2::XMLDocument> MapSerializer::eventTempl;
std::unique_ptr<tinyxml2::XMLDocument> MapSerializer::eventPageTempl;
std::unique_ptr<tinyxml2::XMLDocument> MapSerializer::eventCommandTempl;

Map MapSerializer::FromFile(std::string fileName) 
{
    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) 
    {
        core::Logger::Get()->Log(file.ErrorStr(), core::LogLevel::ERROR);
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
    // Load templates.
    mapTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::MAP);
    eventTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::EVENT);
    eventPageTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::EVENT_PAGE);
    eventCommandTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::EVENT_COMMAND);
    
    // Insert map infos in to the maptree.
    auto* eventTemplateElement = eventTempl->TraverseElement("/Event");
    auto* mapInsertionPoint = mapTempl->TraverseElement("/LMU/Map/events");
    for(auto& event : map.events) 
    {
        eventTemplateElement->DeepCloneInsertBack(mapTempl.get(), mapInsertionPoint);

        auto* eventElement = mapInsertionPoint->TraverseElement("\\Event");
        EventToFileImpl(event, eventElement);
    }

    // TODO: compact could be an argument?
    bool compactMode = false;
    mapTempl->SaveFile(fileName.c_str(), compactMode);
    if (mapTempl->Error()) 
    {
        core::Logger::Get()->Log(mapTempl->ErrorStr(), core::LogLevel::ERROR);
    }

    // Delete Templates.
    mapTempl.reset();
    eventTempl.reset();
    eventPageTempl.reset();
    eventCommandTempl.reset();
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

void MapSerializer::EventToFileImpl(const Event& elem, tinyxml2::XMLElement* eventElem)
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
    auto* eventPageTemplateElement = eventPageTempl->TraverseElement("/EventPage");
    auto* eventInsertionPoint = eventElem->TraverseElement("/pages");
    for(auto& eventPage : elem.eventPages) 
    {
        eventPageTemplateElement->DeepCloneInsertBack(mapTempl.get(), eventInsertionPoint);

        auto* eventPageElement = eventInsertionPoint->TraverseElement("\\EventPage");
        EventPageToFileImpl(eventPage, eventPageElement);
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

void MapSerializer::EventPageToFileImpl(const EventPage& elem, tinyxml2::XMLElement* eventPageElem)
{
    // Set Event ID
    eventPageElem->SetAttribute("id", generateID(elem.id).c_str());

    // Add Event Commands
    auto* eventCommandTemplateElement = eventCommandTempl->TraverseElement("/EventCommand");
    auto* eventPageInsertionPoint = eventPageElem->TraverseElement("/event_commands");
    for(auto& eventCommand : elem.eventCommands) 
    {
        eventCommandTemplateElement->DeepCloneInsertBack(mapTempl.get(), eventPageInsertionPoint);

        auto* eventCommandElement = eventPageInsertionPoint->TraverseElement("\\EventCommand");
        EventCommandSerializer::ToFileImpl(eventCommand, eventCommandElement);
    }
}

};
