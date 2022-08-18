#include "CommonEventSerializer.h"

#include "lcf_serializers/Templates.h"
#include "lcf_serializers/common/EventCommandSerializer.h"

#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>


namespace lcf {

CommonEventSerializer::CommonEventSerializer() {}

// PartialSerializer
CommonEvent CommonEventSerializer::FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) {

    return CommonEvent(1, "", lcf::TriggerType::NONE);
}

std::string FlagToString(bool val) {
    if (val) return "T";
    return "F";
}

std::unique_ptr<tinyxml2::XMLDocument> CommonEventSerializer::ToFile(CommonEvent& elem) {
    auto commonEventTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::COMMON_EVENT);

    // Set Common Event ID
    commonEventTempl->RootElement()->SetAttribute("id", generateID(elem.getID()).c_str());

    // Change Common Event name
    auto* nameElem = commonEventTempl->TraverseElement("/CommonEvent/name")->FirstChild()->ToText();
    nameElem->SetValue(elem.getName().c_str());

    // Change Trigger Type
    auto* triggerElem = commonEventTempl->TraverseElement("/CommonEvent/trigger")->FirstChild();
    triggerElem->SetValue(std::to_string(elem.getTriggerType()).c_str());

    // Add Event Commands
    auto* eventCommandsElem = commonEventTempl->TraverseElement("/CommonEvent/event_commands")->FirstChild();
    for(auto& eventCommand : elem.eventCommands) {
        auto eventCommandDoc = EventCommandSerializer().ToFile(eventCommand);

        eventCommandDoc->DeepCloneInsertBack(commonEventTempl.get(), commonEventTempl->TraverseElement("/CommonEvent/event_commands"));
    }

    return commonEventTempl;
}

// MultiSerializer
std::vector<CommonEvent> CommonEventSerializer::MultipleFromFile(std::string fileName) {
    std::vector<CommonEvent> ret;

    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) {
        std::cout << file.ErrorStr() << std::endl;
        return ret;
    }

    
    return ret;
}

void CommonEventSerializer::MultipleToFile(std::string fileName, std::vector<CommonEvent>& elems) {
};

};
