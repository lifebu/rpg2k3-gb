#include "EventCommandSerializer.h"

#include "lcf_serializers/Templates.h"
#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>
#include <sstream>


namespace lcf 
{

// TODO: Can this be something generic for the RPGHelper?
std::vector<int32_t> parseParamString(std::string& paramString) 
{
    std::vector<int32_t> params;

    std::stringstream stream(paramString);
    std::string temp;
    while (std::getline(stream, temp, ' ')) {
        params.push_back(std::stoi(temp));
    }

    return params;
}

// PartialSerializer
EventCommand EventCommandSerializer::FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) 
{
    return FromFileImpl(doc->TraverseElement("/EventCommand"));
}

// TODO: Can this be something generic for the RPGHelper?
std::string generateParamString(std::vector<int32_t>& params) 
{
    std::string paramString = "";
    for (auto& param : params) 
    {
        std::string emptySpace = param != params.back() ? " " : "";
        paramString.append(std::to_string(param) + emptySpace);
    }

    return paramString;
}

std::unique_ptr<tinyxml2::XMLDocument> EventCommandSerializer::ToFile(EventCommand& elem) 
{
    auto commandTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::EVENT_COMMAND);

    // Change function code
    auto* nameElem = commandTempl->TraverseElement("/EventCommand/code")->FirstChild();
    nameElem->SetValue(std::to_string(elem.type).c_str());

    // Change indentation
    auto* indentElem = commandTempl->TraverseElement("/EventCommand/indent")->FirstChild();
    indentElem->SetValue(std::to_string(elem.indentation).c_str());

    // Change string parameter
    auto* stringElem = commandTempl->TraverseElement("/EventCommand/string")->FirstChild()->ToText();
    stringElem->SetValue(elem.stringParam.c_str());

    // Change parameters
    auto* paramElem = commandTempl->TraverseElement("/EventCommand/parameters")->FirstChild();
    indentElem->SetValue(generateParamString(elem.parameters).c_str());

    return commandTempl;
}

// MultiSerializer
std::vector<EventCommand> EventCommandSerializer::MultipleFromFile(std::string fileName) {
    std::vector<EventCommand> ret;

    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) {
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

    for(auto& eventCommand : elems)
    {
        auto eventCommandFile = ToFile(eventCommand);
        auto* eventCommandElement = eventCommandFile->TraverseElement("/EventCommand");

        eventCommandElement->DeepCloneInsertBack(&file, root);
    }

    file.SaveFile(fileName.c_str());
    if (file.Error()) {
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

};
