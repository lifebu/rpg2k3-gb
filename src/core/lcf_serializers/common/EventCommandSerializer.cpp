#include "EventCommandSerializer.h"

#include "lcf_serializers/Templates.h"
#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>


namespace lcf {

EventCommandSerializer::EventCommandSerializer() {}

// PartialSerializer
EventCommand EventCommandSerializer::FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) {
    return EventCommand(lcf::EventCommand::CommandType::LABEL, 0, "", std::vector<int32_t>());
}

std::string generateParamString(std::vector<int32_t>& params) {
    std::string paramString = "";
    for (auto& param : params) {
        std::string emptySpace = param != params.back() ? " " : "";
        paramString.append(std::to_string(param) + emptySpace);
    }

    return paramString;
}

std::unique_ptr<tinyxml2::XMLDocument> EventCommandSerializer::ToFile(EventCommand& elem) {
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

    
    return ret;
}

void EventCommandSerializer::MultipleToFile(std::string fileName, std::vector<EventCommand>& elems) {
};

};
