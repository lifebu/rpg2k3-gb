#pragma once

#include "../lcf/event/EventCommand.h"

#include <string>

namespace tinyxml2 {class XMLDocument; class XMLElement; };

namespace lcf 
{

class EventCommandSerializer
{
    friend class CommonEventSerializer;

public:
    static std::vector<EventCommand> MultipleFromFile(std::string fileName);
    static void MultipleToFile(std::string fileName, std::vector<EventCommand>& elems);

private:
    static EventCommand FromFileImpl(tinyxml2::XMLElement* eventCommand);
    static void ToFileImpl(const EventCommand& elem, tinyxml2::XMLElement* eventCommand);

    static std::vector<int32_t> parseParamString(const std::string& paramString);
    static std::string generateParamString(const std::vector<int32_t>& params);
};

};