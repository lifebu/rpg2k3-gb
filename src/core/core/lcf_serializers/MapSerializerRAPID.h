#pragma once

#include <string>

namespace rapidxml
{
    template<class Ch> class xml_node;
};

#include "core/lcf/Map.h"

namespace lcf 
{

class MapSerializerRAPID
{
public:
    static Map FromFile(std::string fileName);
    static void ToFile(std::string fileName, Map& map);

private:    
    static Event EventFromFileImpl(rapidxml::xml_node<char>* eventElem);
    static void EventToFileImpl(const Event& elem, rapidxml::xml_node<char>* eventElem);

    static EventPage EventPageFromFileImpl(rapidxml::xml_node<char>* eventPageElem);
    static void EventPageToFileImpl(const EventPage& elem, rapidxml::xml_node<char>* eventPageElem);
};

};