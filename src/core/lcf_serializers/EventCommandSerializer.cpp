#include "EventCommandSerializer.h"

#include "lcf_serializers/Templates.h"
#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>
#include <sstream>

namespace lcf 
{

std::vector<EventCommand> EventCommandSerializer::MultipleFromFile(std::string fileName) 
{
    std::vector<EventCommand> ret;

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
    
    return ret;
}

void EventCommandSerializer::MultipleToFile(std::string fileName, std::vector<EventCommand>& elems) {
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
};

EventCommand EventCommandSerializer::FromFileImpl(tinyxml2::XMLElement* eventCommand)
{
    // Get function code
    auto* nameElem = eventCommand->TraverseElement("/code")->FirstChild();
    int typeVal = std::stoi(nameElem->Value());

    // Get indentation
    auto* indentElem = eventCommand->TraverseElement("/indent")->FirstChild();
    uint8_t indentation = std::stoi(indentElem->Value());

    // Get string parameter
    auto* stringElem = eventCommand->TraverseElement("/string")->FirstChild();
    std::string stringParameter = (stringElem == nullptr) ? "" : stringElem->Value();

    // Get parameters
    auto* paramElem = eventCommand->TraverseElement("/parameters")->FirstChild();
    std::string parameters = (paramElem == nullptr) ? "" : paramElem->Value();

    return EventCommand(EventCommand::CommandType(typeVal), indentation, stringParameter, parseParamString(parameters));
}

void EventCommandSerializer::ToFileImpl(const EventCommand& elem, tinyxml2::XMLElement* eventCommand)
{
    // Change function code
    auto* nameElem = eventCommand->TraverseElement("/code")->FirstChild();
    nameElem->SetValue(std::to_string(elem.type).c_str());

    // Change indentation
    auto* indentElem = eventCommand->TraverseElement("/indent")->FirstChild();
    indentElem->SetValue(std::to_string(elem.indentation).c_str());

    // Change string parameter
    auto* stringElem = eventCommand->TraverseElement("/string")->FirstChild()->ToText();
    stringElem->SetValue(elem.stringParam.c_str());

    // Change parameters
    auto* paramElem = eventCommand->TraverseElement("/parameters")->FirstChild();
    paramElem->SetValue(generateParamString(elem.parameters).c_str());
}

std::vector<int32_t> EventCommandSerializer::parseParamString(const std::string& paramString) 
{
    std::vector<int32_t> params;

    std::stringstream stream(paramString);
    std::string temp;
    while (std::getline(stream, temp, ' ')) {
        params.push_back(std::stoi(temp));
    }

    return params;
}

std::string EventCommandSerializer::generateParamString(const std::vector<int32_t>& params) 
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