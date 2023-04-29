#pragma once

#include "core/emu_interface/RPGMakerInterface.h"

namespace rpgenv 
{

class RPGMakerImpl : public RPGMakerInterface
{
public:
    // Interaction
    void ShowText(std::string text) override;

    // TODO: How can I do let the code know which choice was taken?
    void ShowChoices(std::vector<std::string> choices, lcf::Choices::ChoiceCaseOnCancel cancelBehaviour) override;

    // TODO: How can I do let the code know which number was taken?
    void InputNumber(uint8_t numOfDigits) override;

    // Chara Ram
    void ChangeItem(lcf::ChangeItem::Operation operation, 
        lcf::ChangeItem::ItemIDType idType, uint16_t idTypeValue, 
        lcf::ChangeItem::OperandType operandType, uint16_t operand) override;

    void ChangePartyMember(lcf::ChangePartyMember::Operation operation, 
        lcf::ChangePartyMember::ActorIDType actorIDType, uint16_t actorID) override;

    void ChangeEXP(lcf::ChangeExp::ActorRange, uint16_t actorID, 
        lcf::ChangeExp::Operation operation, lcf::ChangeExp::Operand operand, uint16_t value) override;

    void ChangeParameters(lcf::ChangeParam::ActorRange actorRange, uint16_t actorID, 
        lcf::ChangeParam::Operation operation, lcf::ChangeParam::Parameter parameter, 
        lcf::ChangeParam::Operand operandType, uint16_t operand) override;
    
    // IF operation == CHANGE_EQUIPMENT => operation is used
    // IF operaiton == REMOVE_EQUIPMENT => whichItem is used
    void ChangeEquipment(lcf::ChangeEquip::ActorRange actorRange, uint16_t actorID, 
        lcf::ChangeEquip::Operation operation, lcf::ChangeEquip::ItemIDType itemIDType, 
        lcf::ChangeEquip::Item whichItem, uint16_t itemID) override;

    // Events
    // IF locationType = CONSTANT => xPos and yPos are positions
    // IF locationType = VARIABLE_IDS => xPos and yPos are Variable IDs
    void SetEventLocation(lcf::SetEventLocation::EventIDType eventIDType, 
        lcf::SetEventLocation::LocationType locationType, uint16_t xPos, uint16_t yPos) override;

    // IF locationType = CONSTANT => xPos and yPos are positions
    // IF locationType = VARIABLE_IDS => xPos and yPos are Variable IDs
    uint16_t GetEventID(lcf::GetEventID::LocationType locationType, 
        uint16_t xPos, uint16_t yPos) override;

    // TODO: Maybe this is not part of the interface but is something that is generated based on function calls in the emulator. This might just be used to get the values of the ROM?
    void CallEvent(lcf::CallEvent::EventType eventType, uint16_t eventID, 
        uint16_t pageNumber) override;

    // Rendering
    void ShowPicture(lcf::ShowPicture::PictureIDType pictureIDType, uint16_t pictureID, 
        lcf::ShowPicture::PosType posType, uint16_t xPos, uint16_t yPos, 
        uint8_t red = 100, uint8_t green = 100, uint8_t blue = 100, uint16_t saturation = 100) override;

    // Input
    [[nodiscard]] bool KeyInputProcessing(RPGMAKER::KeyCodes keycode) override;
};

};