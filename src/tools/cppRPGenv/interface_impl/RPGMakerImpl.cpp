#include "RPGMakerImpl.h"

#include "tools/cppRPGenv/manager/InputManager.h"
#include "tools/cppRPGenv/manager/LCFManager.h"
#include "tools/cppRPGenv/manager/RenderManager.h"

namespace rpgenv 
{
// Debug
void RPGMakerImpl::DebugPrint(std::string text)
{
    RenderManager::Get()->ShowText(text);
}

// Interaction
void RPGMakerImpl::ShowText(std::string text)
{

}

void RPGMakerImpl::ShowChoices()
{

}

void RPGMakerImpl::InputNumber()
{

}

// Chara Ram
void RPGMakerImpl::ChangeItem()
{

}

void RPGMakerImpl::ChangePartyMember()
{

}

void RPGMakerImpl::ChangeEXP()
{

}

void RPGMakerImpl::ChangeParameters()
{

}

void RPGMakerImpl::ChangeEquipment()
{

}

// Events
void RPGMakerImpl::SetEventLocation()
{

}

void RPGMakerImpl::GetEventID()
{

}

void RPGMakerImpl::EraseEvent()
{

}

void RPGMakerImpl::CallEvent()
{

}

// Rendering
void RPGMakerImpl::ShowPicture()
{

}

void RPGMakerImpl::ShowHidePlayer()
{

}

// Input
void RPGMakerImpl::KeyInputProcessing()
{

}

};