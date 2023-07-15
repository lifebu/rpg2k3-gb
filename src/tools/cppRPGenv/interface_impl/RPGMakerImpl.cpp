#include "RPGMakerImpl.h"

#include "tools/cppRPGenv/manager/InputManager.h"
#include "tools/cppRPGenv/manager/LCFManager.h"
#include "tools/cppRPGenv/manager/RenderManager.h"
#include "tools/cppRPGenv/system/SystemCore.h"
#include "tools/cppRPGenv/system/SystemStateMachine.h"

namespace rpgenv 
{
// Interaction
void RPGMakerImpl::ShowText(std::string text)
{
    RenderManager::Get()->OpenTextBox(text);
    SystemCore::Get()->ChangeSystemState(SystemStates::PROCESS_TEXTBOX);
}

void RPGMakerImpl::ShowChoices(std::vector<std::string> choices, lcf::Choices::ChoiceCaseOnCancel cancelBehaviour)
{
    RenderManager::Get()->OpenChoiceBox(choices, cancelBehaviour);
    SystemCore::Get()->ChangeSystemState(SystemStates::PROCESS_CHOICES);
}

void RPGMakerImpl::InputNumber(uint8_t numOfDigits)
{
    RenderManager::Get()->OpenNumberInput(numOfDigits);
    SystemCore::Get()->ChangeSystemState(SystemStates::PROCESS_NUMBER_INPUT);
}

// Chara Ram
void RPGMakerImpl::ChangeItem(lcf::ChangeItem::Operation operation, 
    lcf::ChangeItem::ItemIDType idType, uint16_t idTypeValue, 
    lcf::ChangeItem::OperandType operandType, uint16_t operand)
{
    /*
    auto* lcfManager = LCFManager::Get();

    lcf::Item& item = lcfManager->GetDatabase().GetItemByID(idType, idTypeValue);
    int changeBy = operandType == lcf::ChangeItem::Operation::INCREASE ? : ;
    */
}

void RPGMakerImpl::ChangePartyMember(lcf::ChangePartyMember::Operation operation,
    lcf::ChangePartyMember::ActorIDType actorIDType, uint16_t actorID)
{

}

void RPGMakerImpl::ChangeEXP(lcf::ChangeExp::ActorRange, uint16_t actorID, 
    lcf::ChangeExp::Operation operation, lcf::ChangeExp::Operand operand, uint16_t value)
{

}

void RPGMakerImpl::ChangeParameters(lcf::ChangeParam::ActorRange actorRange, uint16_t actorID, 
    lcf::ChangeParam::Operation operation, lcf::ChangeParam::Parameter parameter, 
    lcf::ChangeParam::Operand operandType, uint16_t operand)
{

}

void RPGMakerImpl::ChangeEquipment(lcf::ChangeEquip::ActorRange actorRange, uint16_t actorID, 
    lcf::ChangeEquip::Operation operation, lcf::ChangeEquip::ItemIDType itemIDType, 
    lcf::ChangeEquip::Item whichItem, uint16_t itemID)
{

}

// Events
void RPGMakerImpl::SetEventLocation(lcf::SetEventLocation::EventIDType eventIDType, 
    lcf::SetEventLocation::LocationType locationType, uint16_t xPos, uint16_t yPos)
{

}

uint16_t RPGMakerImpl::GetEventID(lcf::GetEventID::LocationType locationType, 
    uint16_t xPos, uint16_t yPos)
{
    return 0;
}

void RPGMakerImpl::CallEvent(lcf::CallEvent::EventType eventType, uint16_t eventID, 
    uint16_t pageNumber)
{
    // TODO: The code will use this to read the ROM and RAM on the Map, so do not call the actual database but write to the expected variables like the generated code would.
    return;
}

// Rendering
void RPGMakerImpl::ShowPicture(lcf::ShowPicture::PictureIDType pictureIDType, uint16_t pictureID, 
    lcf::ShowPicture::PosType posType, uint16_t xPos, uint16_t yPos, 
    float red /*= 1.0f*/, float green /*= 1.0f*/, float blue /*= 1.0f*/, float saturation /*= 1.0f*/)
{

}

// Input
bool RPGMakerImpl::KeyInputProcessing(RPGMAKER::KeyCodes keycode)
{
    return rpgenv::InputManager::Get()->isKeyPressed(keycode);
}

};