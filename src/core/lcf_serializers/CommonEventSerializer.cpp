#include "CommonEventSerializer.h"

#include "Templates.h"
#include "EventCommandSerializer.h"

#include "src/core/utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>


namespace lcf {

CommonEvent CommonEventSerializer::FromFile(std::string fileName) {
    /*
    std::string name = "";
    uint16_t id = 1;
    
    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) {
        std::cout << file.ErrorStr() << std::endl;
        return Switch(id, name);
    }

    auto* nameElem = file.TraverseElement("/Switch/name")->FirstChild()->ToText();
    name = nameElem->Value();
    id = file.RootElement()->UnsignedAttribute("id");
    */

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
        auto eventCommandDoc = EventCommandSerializer::ToFile(eventCommand);

        eventCommandDoc->DeepCloneInsertBack(commonEventTempl.get(), commonEventTempl->TraverseElement("/CommonEvent/event_commands"));
    }

    return commonEventTempl;
}

};
