#include "MapSerializerRAPID.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <rapidxml/rapidxml_ext.hpp>

#include "core/lcf_serializers/Templates.h"
#include "core/lcf_serializers/EventCommandSerializerRAPID.h"
#include "core/utilities/RPGHelper.h"


namespace lcf 
{

Map MapSerializerRAPID::FromFile(std::string fileName) 
{
    rapidxml::file file(fileName.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(file.data());

    Map map = Map(0);

    auto* currentMapEvent = doc.first_node("LMU")->first_node("Map")->first_node("events")->first_node("Event");
    while(currentMapEvent)
    {
        Event newEvent = EventFromFileImpl(currentMapEvent);
        map.addEvent(newEvent);
        currentMapEvent = currentMapEvent->next_sibling();
    }

    return map;
}

void MapSerializerRAPID::ToFile(std::string fileName, Map& map) 
{
    rapidxml::file file1(TEMPLATES::MAP);
    rapidxml::xml_document<> mapTempl;
    mapTempl.parse<0>(file1.data());

    int size = map.events.size();

    // Insert map infos in to the maptree.
    for(auto& event : map.events) 
    {
        // TODO: This does not feel great but greatly reduces memory (because otherwise each iteration influences each other)
        // TODO: Maybe make a copy of template every iteration?
        rapidxml::file file2(TEMPLATES::EVENT);
        rapidxml::xml_document<> eventTempl;
        eventTempl.parse<0>(file2.data());

        auto* eventElement = eventTempl.first_node("Event");
        EventToFileImpl(event, eventElement);

        auto* whereToInsert = mapTempl.first_node("LMU")->first_node("Map")->first_node("events");
        whereToInsert->insert_node(nullptr, whereToInsert->document()->clone_node(eventElement));
    }

    std::ofstream output(fileName);
    if(!output.is_open())
    {
        // TODO: log this error!
        return;
    }
    output << mapTempl;
    output.close();
}

Event MapSerializerRAPID::EventFromFileImpl(rapidxml::xml_node<>* eventElem)
{
    // Get Event ID
    uint16_t id = std::stoi(eventElem->first_attribute("id")->value());

    // Get Event Name.
    auto* nameElem = eventElem->first_node("name")->first_node();
    std::string name = (nameElem == nullptr) ? "" : nameElem->value();

    // Get Event Coordinates
    auto* xCoordElem = eventElem->first_node("x")->first_node();
    uint16_t x = std::stoi(xCoordElem->value());

    auto* yCoordElem = eventElem->first_node("y")->first_node();
    uint16_t y = std::stoi(yCoordElem->value());

    Event newEvent = Event(id, name, x, y);
    auto* currentPage = eventElem->first_node("pages")->first_node("EventPage");
    while(currentPage)
    {
        EventPage newEventPage = EventPageFromFileImpl(currentPage);
        newEvent.addEventPage(newEventPage);

        currentPage = currentPage->next_sibling();
    }

    return newEvent;
}

void MapSerializerRAPID::EventToFileImpl(const Event& elem, rapidxml::xml_node<>* eventElem)
{
    // Set Event ID
    eventElem->first_attribute("id")->value(generateID(elem.id).c_str());

    // Set Event Name
    auto* nameElem = eventElem->first_node("name")->first_node();
    nameElem->value(elem.name.c_str());

    // Set Event Coordinates
    auto* xCoordElem = eventElem->first_node("x")->first_node();
    xCoordElem->value(std::to_string(elem.x).c_str());
    
    auto* yCoordElem = eventElem->first_node("y")->first_node();
    yCoordElem->value(std::to_string(elem.x).c_str());

    // Insert Event Pages
    for(auto& eventPage : elem.eventPages) 
    {
        // TODO: This does not feel great but greatly reduces memory (because otherwise each iteration influences each other)
        // TODO: I may need something to cut the pages of the eventElem away before generation? (delete every child in /pages) at the start of this function?
        // TODO: Maybe make a copy of template every iteration?
        rapidxml::file file1(TEMPLATES::EVENT_PAGE);
        rapidxml::xml_document<> eventPageTempl;
        eventPageTempl.parse<0>(file1.data());

        auto* eventPageElement = eventPageTempl.first_node("EventPage");
        EventPageToFileImpl(eventPage, eventPageElement);

        auto* whereToInsert = eventElem->first_node("pages");
        whereToInsert->insert_node(nullptr, whereToInsert->document()->clone_node(eventPageElement));
    }
}

EventPage MapSerializerRAPID::EventPageFromFileImpl(rapidxml::xml_node<>* eventPageElem)
{
    // Get Event ID
    uint16_t id = std::stoi(eventPageElem->first_attribute("id")->value());

    // Get EventCommands
    EventPage newEventPage = EventPage(id);
    auto* currentEventCommand = eventPageElem->first_node("event_commands")->first_node("EventCommand");
    while(currentEventCommand)
    {
        EventCommand newEventCommands = EventCommandSerializerRAPID::FromFileImpl(currentEventCommand);
        newEventPage.addEventCommand(newEventCommands);

        currentEventCommand = currentEventCommand->next_sibling();
    }

    return newEventPage;
}

void MapSerializerRAPID::EventPageToFileImpl(const EventPage& elem, rapidxml::xml_node<>* eventPageElem)
{
    // Set Event ID
    eventPageElem->first_attribute("id")->value(generateID(elem.id).c_str());

    // Add Event Commands
    for(auto& eventCommand : elem.eventCommands)
    {
        // TODO: This does not feel great but greatly reduces memory (because otherwise each iteration influences each other)
        // TODO: I may need something to cut the commands of the eventPageElem away before generation? (delete every child in /event_commands) at the start of this function?
        // TODO: Maybe make a copy of template every iteration?
        rapidxml::file file1(TEMPLATES::EVENT_COMMAND);
        rapidxml::xml_document<> eventCommandTempl;
        eventCommandTempl.parse<0>(file1.data());

        auto* eventCommandElem = eventCommandTempl.first_node("EventCommand");
        EventCommandSerializerRAPID::ToFileImpl(eventCommand, eventCommandElem);

        auto* whereToInsert = eventPageElem->first_node("event_commands");
        whereToInsert->insert_node(nullptr, whereToInsert->document()->clone_node(eventCommandElem));
    }
}

};
