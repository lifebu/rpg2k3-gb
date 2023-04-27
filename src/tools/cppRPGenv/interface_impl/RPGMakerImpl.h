#pragma once

#include "../interface/RPGMakerInterface.h"

namespace rpgenv 
{

class RPGMakerImpl : public RPGMakerInterface
{
    // Debug & Menu
    void ShowText() override;
    void ShowChoices() override;
    void InputNumber() override;

    // Chara Ram
    void ChangeItem() override;
    void ChangePartyMember() override;
    void ChangeEXP() override;
    void ChangeParameters() override;
    void ChangeEquipment() override;

    // Events
    void SetEventLocation() override;
    void GetEventID() override;
    void EraseEvent() override;
    void CallEvent() override;

    // Rendering
    void ShowPicture() override;
    void ShowHidePlayer() override;

    // Input
    void KeyInputProcessing() override;
};

};