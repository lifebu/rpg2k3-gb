#include "EventCommandSerializerRAPID.h"

#include <iostream>
#include <sstream>

#include <rapidxml/rapidxml_ext.hpp>

#include "core/lcf_serializers/Templates.h"

namespace lcf 
{

std::vector<EventCommand> EventCommandSerializerRAPID::MultipleFromFile(std::string fileName) 
{
    std::vector<EventCommand> ret;

    rapidxml::file file(fileName.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(file.data());

    auto* currentCommand = doc.first_node("EventCommand");
    while(currentCommand)
    {
        ret.emplace_back(FromFileImpl(currentCommand));
        currentCommand = currentCommand->next_sibling();
    }
    
    return ret;
}

void EventCommandSerializerRAPID::MultipleToFile(std::string fileName, std::vector<EventCommand>& elems) 
{
    rapidxml::file file(fileName.c_str());
    rapidxml::xml_document<> doc;
    doc.parse<0>(file.data());

    rapidxml::file file1(TEMPLATES::EVENT_COMMAND);
    rapidxml::xml_document<> commandTempl;
    commandTempl.parse<0>(file1.data());

    for(auto& eventCommand : elems)
    {
        auto* eventCommandElement = commandTempl.first_node("EventCommand");
        ToFileImpl(eventCommand, eventCommandElement);
        
        auto* whereToInsert = doc.last_node("EventCommand");
        whereToInsert->insert_node(nullptr, whereToInsert->document()->clone_node(eventCommandElement));
    }

    std::ofstream output(fileName);
    if(!output.is_open())
    {
        // TODO: log this error!
        return;
    }
    output << doc;
    output.close();
};

EventCommand EventCommandSerializerRAPID::FromFileImpl(rapidxml::xml_node<>* eventCommand)
{
    // Get function code
    auto* nameElem = eventCommand->first_node("code")->first_node();
    int typeVal = std::stoi(nameElem->value());

    // Get indentation
    auto* indentElem = eventCommand->first_node("indent")->first_node();
    uint8_t indentation = std::stoi(indentElem->value());

    // Get string parameter
    auto* stringElem = eventCommand->first_node("string")->first_node();
    std::string stringParameter = (stringElem == nullptr) ? "" : stringElem->value();

    // Get parameters
    auto* paramElem = eventCommand->first_node("parameters")->first_node();
    std::string parameters = (paramElem == nullptr) ? "" : paramElem->value();

    return EventCommand(EventCommand::CommandType(typeVal), indentation, stringParameter, parseParamString(parameters));
}

void EventCommandSerializerRAPID::ToFileImpl(const EventCommand& elem, rapidxml::xml_node<>* eventCommand)
{
    // Change function code
    auto* nameElem = eventCommand->first_node("code")->first_node();
    nameElem->value(std::to_string(elem.type).c_str());

    // Change indentation
    auto* indentElem = eventCommand->first_node("indent")->first_node();
    indentElem->value(std::to_string(elem.indentation).c_str());

    // Change string parameter
    auto* stringElem = eventCommand->first_node("string")->first_node();
    stringElem->value(elem.stringParam.c_str());

    // Change parameters
    auto* paramElem = eventCommand->first_node("parameters")->first_node();
    paramElem->value(generateParamString(elem.parameters).c_str());
}

std::vector<int32_t> EventCommandSerializerRAPID::parseParamString(const std::string& paramString) 
{
    std::vector<int32_t> params;

    std::stringstream stream(paramString);
    std::string temp;
    while (std::getline(stream, temp, ' ')) {
        params.push_back(std::stoi(temp));
    }

    return params;
}

std::string EventCommandSerializerRAPID::generateParamString(const std::vector<int32_t>& params) 
{
    std::string paramString = "";
    for (auto& param : params) 
    {
        std::string emptySpace = param != params.back() ? " " : "";
        paramString.append(std::to_string(param) + emptySpace);
    }

    return paramString;
}

};
