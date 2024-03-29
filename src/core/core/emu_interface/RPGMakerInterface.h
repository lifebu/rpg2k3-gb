#pragma once

#include <string>
#include <vector>

#include "core/def/RPGMaker.h"
#include "core/lcf/event/EventCommandFactoryDef.h"
#include "core/structure/Singleton.h"

namespace rpgenv
{

class RPGMakerInterface : public Singleton<RPGMakerInterface>
{
public:
    // Interaction
    virtual void ShowText(std::string text) = 0;
    
    // TODO: How can I do let the code know which choice was taken?
    virtual void ShowChoices(std::vector<std::string> choices, lcf::Choices::ChoiceCaseOnCancel cancelBehaviour) = 0;

    // TODO: How can I do let the code know which number was taken?
    virtual void InputNumber(uint8_t numOfDigits) = 0;

    // Chara Ram
    virtual void ChangeItem(lcf::ChangeItem::Operation operation, 
        lcf::ChangeItem::ItemIDType idType, uint16_t idTypeValue, 
        lcf::ChangeItem::OperandType operandType, uint16_t operand) = 0;
    
    virtual void ChangePartyMember(lcf::ChangePartyMember::Operation operation, 
        lcf::ChangePartyMember::ActorIDType actorIDType, uint16_t actorID) = 0;

    virtual void ChangeEXP(uint16_t actorID, uint32_t value) = 0;

    virtual void ChangeParameters(uint16_t actorID, lcf::ChangeParam::Parameter parameter, uint16_t value) = 0;
    
    // IF operation == CHANGE_EQUIPMENT => operation is used
    // IF operaiton == REMOVE_EQUIPMENT => whichItem is used
    virtual void ChangeEquipment(uint16_t actorID, lcf::ChangeEquip::Item whichItem, uint16_t itemID) = 0;
    
    // Variables
    virtual int32_t ControlVariables(uint16_t id) = 0;
    virtual void ControlVariables(uint16_t id, int32_t value) = 0;
    // These are all functionalities that ControlVariables in RPG Maker provides, but we use shortforms here to not make it as convoluted.
    virtual uint16_t ControlVariables_GetEventXPos(uint16_t eventID) = 0;
    virtual void ControlVariables_SetEventXPos(uint16_t eventID, uint16_t eventXPos) = 0;
    virtual uint16_t ControlVariables_GetEventYPos(uint16_t eventID) = 0;
    virtual void ControlVariables_SetEventYPos(uint16_t eventID, uint16_t eventYPos) = 0;

    virtual uint32_t ControlVariables_GetCharEXP(uint16_t charID) = 0;
    virtual uint16_t ControlVariables_GetCharParameter(uint16_t charID, lcf::ChangeParam::Parameter parameter) = 0;
    virtual uint16_t ControlVariables_GetCharItemID(uint16_t charID, lcf::ChangeEquip::Item whichItem) = 0;

    // Events
    // IF locationType = CONSTANT => xPos and yPos are positions
    // IF locationType = VARIABLE_IDS => xPos and yPos are Variable IDs
    virtual void SetEventLocation(uint16_t eventID, 
        lcf::SetEventLocation::LocationType locationType, uint16_t xPos, uint16_t yPos) = 0;

    // IF locationType = CONSTANT => xPos and yPos are positions
    // IF locationType = VARIABLE_IDS => xPos and yPos are Variable IDs
    virtual uint16_t GetEventID(lcf::GetEventID::LocationType locationType, 
        uint16_t xPos, uint16_t yPos) = 0;
    
    // TODO: Maybe this is not part of the interface but is something that is generated based on function calls in the emulator. This might just be used to get the values of the ROM?
    virtual void CallEvent(lcf::CallEvent::EventType eventType, uint16_t eventID, 
        uint16_t pageID) = 0;

    // Rendering
    virtual void ShowPicture(lcf::ShowPicture::PictureIDType pictureIDType, uint16_t pictureID, 
        lcf::ShowPicture::PosType posType, uint16_t xPos, uint16_t yPos, 
        float red = 1.0f, float green = 1.0f, float blue = 1.0f, float saturation = 1.0f) = 0;

    // Input
    [[nodiscard]] virtual bool KeyInputProcessing(RPGMAKER::KeyCodes keycode) = 0;
};

};