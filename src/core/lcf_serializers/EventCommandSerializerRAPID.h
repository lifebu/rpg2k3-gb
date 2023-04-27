#pragma once

#include "../lcf/event/EventCommand.h"

#include <string>

// TODO: How to have the include in the cpp?
// TODO: Why is this include so strange??
#include "../../../thirdparty/rapidxml/rapidxml_ext.hpp"

namespace lcf 
{

class EventCommandSerializerRAPID
{
    friend class MapSerializerRAPID;

public:
    static std::vector<EventCommand> MultipleFromFile(std::string fileName);
    static void MultipleToFile(std::string fileName, std::vector<EventCommand>& elems);

private:
    static EventCommand FromFileImpl(rapidxml::xml_node<>* eventCommand);
    static void ToFileImpl(const EventCommand& elem, rapidxml::xml_node<>* eventCommand);

    static std::vector<int32_t> parseParamString(const std::string& paramString);
    static std::string generateParamString(const std::vector<int32_t>& params);
};

};