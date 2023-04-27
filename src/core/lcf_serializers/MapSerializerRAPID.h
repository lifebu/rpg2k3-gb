#pragma once

#include "../lcf/Map.h"

#include <string>

// TODO: How to have the include in the cpp?
// TODO: Why is this include so strange??
#include "../../../thirdparty/rapidxml/rapidxml_ext.hpp"

namespace lcf 
{

class MapSerializerRAPID
{
public:
    static Map FromFile(std::string fileName);
    static void ToFile(std::string fileName, Map& map);

private:    
    static Event EventFromFileImpl(rapidxml::xml_node<>* eventElem);
    static void EventToFileImpl(const Event& elem, rapidxml::xml_node<>* eventElem);

    static EventPage EventPageFromFileImpl(rapidxml::xml_node<>* eventPageElem);
    static void EventPageToFileImpl(const EventPage& elem, rapidxml::xml_node<>* eventPageElem);
};

};