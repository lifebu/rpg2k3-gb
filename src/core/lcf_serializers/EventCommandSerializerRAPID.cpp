#include "EventCommandSerializerRAPID.h"

#include "lcf_serializers/Templates.h"
#include "utilities/RPGHelper.h"
#include "thirdparty/rapidxml/rapidxml_ext.hpp"

#include <iostream>
#include <sstream>

namespace lcf 
{

std::vector<EventCommand> EventCommandSerializerRAPID::MultipleFromFile(std::string fileName) 
{
    std::vector<EventCommand> ret;
    /*
    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) 
    {
        std::cout << file.ErrorStr() << std::endl;
        return ret;
    }

    auto* currentCommand = file.TraverseElement("/EventCommand");
    while(currentCommand)
    {
        ret.emplace_back(FromFileImpl(currentCommand));
        currentCommand = currentCommand->NextSiblingElement();
    }
    */
    
    return ret;
}

void EventCommandSerializerRAPID::MultipleToFile(std::string fileName, std::vector<EventCommand>& elems) {
    /*
    auto file = tinyxml2::XMLDocument();
    auto* root = file.RootElement();

    tinyxml2::XMLDocument commandTempl(TEMPLATES::EVENT_COMMAND);
    for(auto& eventCommand : elems)
    {
        auto* eventCommandElement = commandTempl.TraverseElement("/EventCommand");
        ToFileImpl(eventCommand, eventCommandElement);
        
        eventCommandElement->DeepCloneInsertBack(&file, root);
    }

    file.SaveFile(fileName.c_str());
    if (file.Error()) 
    {
        std::cout << file.ErrorStr() << std::endl;
        return;
    }
    */
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
    indentElem->value(generateParamString(elem.parameters).c_str());
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
