#pragma once

#include <string>

namespace rapidxml
{
    template<class Ch> class xml_node;
};

#include "core/lcf/event/EventCommand.h"

namespace lcf 
{

class EventCommandSerializerRAPID
{
    friend class MapSerializerRAPID;

public:
    static std::vector<EventCommand> MultipleFromFile(std::string fileName);
    static void MultipleToFile(std::string fileName, std::vector<EventCommand>& elems);

private:
    static EventCommand FromFileImpl(rapidxml::xml_node<char>* eventCommand);
    static void ToFileImpl(const EventCommand& elem, rapidxml::xml_node<char>* eventCommand);

    static std::vector<int32_t> parseParamString(const std::string& paramString);
    static std::string generateParamString(const std::vector<int32_t>& params);
};

};