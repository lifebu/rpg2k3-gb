#pragma once

#include <core/emu_interface/RPGMakerInterface.h>

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

    void ChangeEXP(uint16_t actorID, uint32_t value) override;

    void ChangeParameters(uint16_t actorID, lcf::ChangeParam::Parameter parameter, uint16_t value) override;
    
    // IF operation == CHANGE_EQUIPMENT => operation is used
    // IF operaiton == REMOVE_EQUIPMENT => whichItem is used
    void ChangeEquipment(uint16_t actorID, lcf::ChangeEquip::Item whichItem, uint16_t itemID) override;

    // Variables
    int32_t ControlVariables(uint16_t id) override;
    void ControlVariables(uint16_t id, int32_t value) override;
    // These are all functionalities that ControlVariables in RPG Maker provides, but we use shortforms here to not make it as convoluted.
    uint16_t ControlVariables_GetEventXPos(uint16_t eventID) override;
    void ControlVariables_SetEventXPos(uint16_t eventID, uint16_t eventXPos) override;
    uint16_t ControlVariables_GetEventYPos(uint16_t eventID) override;
    void ControlVariables_SetEventYPos(uint16_t eventID, uint16_t eventYPos) override;

    uint32_t ControlVariables_GetCharEXP(uint16_t charID) override;
    uint16_t ControlVariables_GetCharParameter(uint16_t charID, lcf::ChangeParam::Parameter parameter) override;
    uint16_t ControlVariables_GetCharItemID(uint16_t charID, lcf::ChangeEquip::Item whichItem) override;


    // Events
    // IF locationType = CONSTANT => xPos and yPos are positions
    // IF locationType = VARIABLE_IDS => xPos and yPos are Variable IDs
    void SetEventLocation(uint16_t eventID, 
        lcf::SetEventLocation::LocationType locationType, uint16_t xPos, uint16_t yPos) override;

    // IF locationType = CONSTANT => xPos and yPos are positions
    // IF locationType = VARIABLE_IDS => xPos and yPos are Variable IDs
    uint16_t GetEventID(lcf::GetEventID::LocationType locationType, 
        uint16_t xPos, uint16_t yPos) override;

    void CallEvent(lcf::CallEvent::EventType eventType, uint16_t eventID, 
        uint16_t pageID) override;

    // Rendering
    void ShowPicture(lcf::ShowPicture::PictureIDType pictureIDType, uint16_t pictureID, 
        lcf::ShowPicture::PosType posType, uint16_t xPos, uint16_t yPos, 
        float red = 1.0f, float green = 1.0f, float blue = 1.0f, float saturation = 1.0f) override;

    // Input
    [[nodiscard]] bool KeyInputProcessing(RPGMAKER::KeyCodes keycode) override;
};

};