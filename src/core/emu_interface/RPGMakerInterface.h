#pragma once

#include <string>
#include <vector>

#include "core/def/RPGMaker.h"
#include "core/lcf/event/EventCommandFactoryDef.h"

namespace rpgenv
{

class RPGMakerInterface
{
public:
    // Debug
    virtual void DebugPrint(std::string text) = 0;

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

    virtual void ChangeEXP(lcf::ChangeExp::ActorRange, uint16_t actorID, 
        lcf::ChangeExp::Operation operation, lcf::ChangeExp::Operand operand, uint16_t value) = 0;

    virtual void ChangeParameters(lcf::ChangeParam::ActorRange actorRange, uint16_t actorID, 
        lcf::ChangeParam::Operation operation, lcf::ChangeParam::Parameter parameter, 
        lcf::ChangeParam::Operand operandType, uint16_t operand) = 0;
    
    // IF operation == CHANGE_EQUIPMENT => operation is used
    // IF operaiton == REMOVE_EQUIPMENT => whichItem is used
    virtual void ChangeEquipment(lcf::ChangeEquip::ActorRange actorRange, uint16_t actorID, 
        lcf::ChangeEquip::Operation operation, lcf::ChangeEquip::ItemIDType itemIDType, 
        lcf::ChangeEquip::Item whichItem, uint16_t itemID) = 0;

    // Events
    // IF locationType = CONSTANT => xPos and yPos are positions
    // IF locationType = VARIABLE_IDS => xPos and yPos are Variable IDs
    virtual void SetEventLocation(lcf::SetEventLocation::EventIDType eventIDType, 
        lcf::SetEventLocation::LocationType locationType, uint16_t xPos, uint16_t yPos) = 0;

    // IF locationType = CONSTANT => xPos and yPos are positions
    // IF locationType = VARIABLE_IDS => xPos and yPos are Variable IDs
    virtual uint16_t GetEventID(lcf::GetEventID::LocationType locationType, 
        uint16_t xPos, uint16_t yPos) = 0;
    
    // TODO: Maybe this is not part of the interface but is something that is generated based on function calls in the emulator. This might just be used to get the values of the ROM?
    virtual void CallEvent(lcf::CallEvent::EventType eventType, uint16_t eventID, 
        uint16_t pageNumber) = 0;

    // Rendering
    virtual void ShowPicture(lcf::ShowPicture::PictureIDType pictureIDType, uint16_t pictureID, 
        lcf::ShowPicture::PosType posType, uint16_t xPos, uint16_t yPos, 
        uint8_t red = 100, uint8_t green = 100, uint8_t blue = 100, uint16_t saturation = 100) = 0;
    
    virtual void ShowHidePlayer(lcf::ShowHidePlayer::Visibility visibility) = 0;

    // Input
    [[nodiscard]] virtual bool KeyInputProcessing(RPGMAKER::KeyCodes keycode) = 0;
};

};