#pragma once

#include "../lcf/Map.h"

#include <memory>
#include <string>

namespace tinyxml2 {class XMLDocument; class XMLElement;};

namespace lcf 
{

class MapSerializer
{
public:
    static Map FromFile(std::string fileName);
    static void ToFile(std::string fileName, Map& map);

private:
    static Event EventFromFileImpl(tinyxml2::XMLElement* eventElem);
    static void EventToFileImpl(const Event& elem, tinyxml2::XMLElement* eventElem);

    static EventPage EventPageFromFileImpl(tinyxml2::XMLElement* eventPageElem);
    static void EventPageToFileImpl(const EventPage& elem, tinyxml2::XMLElement* eventPageElem);

private:
    static std::unique_ptr<tinyxml2::XMLDocument> mapTempl;
    static std::unique_ptr<tinyxml2::XMLDocument> eventTempl;
    static std::unique_ptr<tinyxml2::XMLDocument> eventPageTempl;
    static std::unique_ptr<tinyxml2::XMLDocument> eventCommandTempl;
};

};