#include "CommonEventSerializer.h"

#include "lcf_serializers/Templates.h"
#include "lcf_serializers/EventCommandSerializer.h"

#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>


namespace lcf 
{

std::vector<CommonEvent> CommonEventSerializer::MultipleFromFile(std::string fileName)
{
    std::vector<CommonEvent> ret;

    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) 
    {
        std::cout << file.ErrorStr() << std::endl;
        return ret;
    }

    auto* currentCommonEvent = file.TraverseElement("/CommonEvent");
    while(currentCommonEvent)
    {
        ret.emplace_back(FromFileImpl(currentCommonEvent));
        currentCommonEvent = currentCommonEvent->NextSiblingElement();
    }
    
    return ret;
}

void CommonEventSerializer::MultipleToFile(std::string fileName, std::vector<CommonEvent>& elems)
{
    tinyxml2::XMLDocument commonEventTempl(TEMPLATES::COMMON_EVENT);
    auto file = tinyxml2::XMLDocument();
    auto* root = file.RootElement();

    for(auto& eventCommand : elems)
    {
        auto* eventCommandElement = commonEventTempl.TraverseElement("/CommonEvent");
        ToFileImpl(eventCommand, &commonEventTempl, eventCommandElement);
        
        eventCommandElement->DeepCloneInsertBack(&file, root);
    }

    file.SaveFile(fileName.c_str());
    if (file.Error()) 
    {
        std::cout << file.ErrorStr() << std::endl;
        return;
    }
};

CommonEvent CommonEventSerializer::FromFileImpl(tinyxml2::XMLElement* commonEvent)
{
    // Get Common Event ID
    uint16_t id = std::stoi(commonEvent->Attribute("id"));

    // Get Common Event name
    auto* nameElem = commonEvent->TraverseElement("/name")->FirstChild()->ToText();
    std::string name = (nameElem == nullptr) ? "" : nameElem->Value();
    
    // Get Trigger Type
    auto* triggerElem = commonEvent->TraverseElement("/trigger")->FirstChild();
    CommonEvent::TriggerType trigger = static_cast<CommonEvent::TriggerType>(std::stoi(triggerElem->Value()));

    // No Support for Switch Flag and Switch ID

    CommonEvent newElement = CommonEvent(id, name, trigger);

    // Get Event Commands
    auto* currentCommand = commonEvent->TraverseElement("event_commands/EventCommand");
    while(currentCommand)
    {
        EventCommand newCommand = EventCommandSerializer::FromFileImpl(currentCommand);
        newElement.addEventCommand(newCommand);
        currentCommand = currentCommand->NextSiblingElement();
    }

    return newElement;
}

void CommonEventSerializer::ToFileImpl(const CommonEvent& elem, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* commonEvent)
{
    tinyxml2::XMLDocument commandTempl(TEMPLATES::EVENT_COMMAND);

    // Set Common Event ID
    commonEvent->SetAttribute("id", generateID(elem.id).c_str());

    // Change Common Event name
    auto* nameElem = commonEvent->TraverseElement("/name")->FirstChild()->ToText();
    nameElem->SetValue(elem.name.c_str());

    // Change Trigger Type
    auto* triggerElem = commonEvent->TraverseElement("/trigger")->FirstChild();
    triggerElem->SetValue(std::to_string(elem.trigger).c_str());

    // No Support for Switch Flag and Switch ID

    // Add Event Commands
    for(auto& eventCommand : elem.eventCommands) 
    {
        auto* eventCommandElement = commandTempl.TraverseElement("/EventCommand");
        EventCommandSerializer::ToFileImpl(eventCommand, eventCommandElement);

        eventCommandElement->DeepCloneInsertBack(doc, commonEvent->TraverseElement("/event_commands"));
    }
}

};
