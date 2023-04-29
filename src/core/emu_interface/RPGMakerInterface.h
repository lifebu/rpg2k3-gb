#pragma once

namespace rpgenv 
{

class RPGMakerInterface
{
public:
    // Debug & Menu
    virtual void ShowText() = 0;
    virtual void ShowChoices() = 0;
    virtual void InputNumber() = 0;

    // Chara Ram
    virtual void ChangeItem() = 0;
    virtual void ChangePartyMember() = 0;
    virtual void ChangeEXP() = 0;
    virtual void ChangeParameters() = 0;
    virtual void ChangeEquipment() = 0;

    // Events
    virtual void SetEventLocation() = 0;
    virtual void GetEventID() = 0;
    virtual void EraseEvent() = 0;
    // TODO: Maybe this is not part of the interface but is something that is generated based on function calls in the emulator.
    virtual void CallEvent() = 0;

    // Rendering
    virtual void ShowPicture() = 0;
    virtual void ShowHidePlayer() = 0;

    // Input
    virtual void KeyInputProcessing() = 0;
};

};