
#include "RPGMakerImpl.h"

#include "core/def/MemorySizes.h"
#include "core/def/VarMapping.h"
#include "tools/cppRPGenv/manager/InputManager.h"
#include "tools/cppRPGenv/manager/LCFManager.h"
#include "tools/cppRPGenv/manager/RenderManager.h"
#include "tools/cppRPGenv/manager/VariableManager.h"
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
    assert(idTypeValue >= RPGMAKER::MIN_ID && idTypeValue <= RPGMAKER::MAX_ID);

    auto* lcfManager = LCFManager::Get();
    assert(lcfManager);

    lcf::Item* item = lcfManager->GetDatabase().GetItemByID(idTypeValue);
    assert(item);

    int8_t factor = operation == lcf::ChangeItem::Operation::INCREASE ? 1: -1;
    item->amount += operand * factor;
}

void RPGMakerImpl::ChangePartyMember(lcf::ChangePartyMember::Operation operation,
    lcf::ChangePartyMember::ActorIDType actorIDType, uint16_t actorID)
{
    assert(actorID >= RPGMAKER::MIN_ID && actorID <= RPGMAKER::MAX_NUM_CHARS);

    auto* lcfManager = LCFManager::Get();
    assert(lcfManager);

    lcf::Character* character = lcfManager->GetDatabase().GetCharacterByID(actorID);
    assert(character);

    bool partyValue = operation == lcf::ChangePartyMember::Operation::ADD ? true : false;
    character->isInParty = partyValue;
}

void RPGMakerImpl::ChangeEXP(lcf::ChangeExp::ActorRange actorRange, uint16_t actorID, 
    lcf::ChangeExp::Operation operation, lcf::ChangeExp::Operand operand, uint16_t value)
{
    assert(actorID >= RPGMAKER::MIN_ID && actorID <= RPGMAKER::MAX_NUM_CHARS);

    auto* lcfManager = LCFManager::Get();
    assert(lcfManager);

    lcf::Character* character = lcfManager->GetDatabase().GetCharacterByID(actorID);
    assert(character);

    int8_t factor = operation == lcf::ChangeExp::Operation::INCREASE ? 1: -1;
    character->exp += value * factor;
}

void RPGMakerImpl::ChangeParameters(lcf::ChangeParam::ActorRange actorRange, uint16_t actorID, 
    lcf::ChangeParam::Operation operation, lcf::ChangeParam::Parameter parameter, 
    lcf::ChangeParam::Operand operandType, uint16_t operand)
{
    assert(actorID >= RPGMAKER::MIN_ID && actorID <= RPGMAKER::MAX_NUM_CHARS);

    auto* lcfManager = LCFManager::Get();
    assert(lcfManager);

    lcf::Character* character = lcfManager->GetDatabase().GetCharacterByID(actorID);
    assert(character);

    int8_t factor = operation == lcf::ChangeParam::Operation::INCREASE ? 1: -1;
    int16_t delta = operand * factor;

    switch(parameter)
    {
        case lcf::ChangeParam::Parameter::MAX_HP:
            character->maxHP += delta;
            break;
        case lcf::ChangeParam::Parameter::MAX_MP:
            character->maxMP += delta;
            break;
        case lcf::ChangeParam::Parameter::ATTACK:
            character->attack += delta;
            break;
        case lcf::ChangeParam::Parameter::DEFENSE:
            character->defense += delta;
            break;
        case lcf::ChangeParam::Parameter::MIND:
            character->mind += delta;
            break;
        case lcf::ChangeParam::Parameter::AGILITY:
            character->agility += delta;
            break;
    }
}

void RPGMakerImpl::ChangeEquipment(lcf::ChangeEquip::ActorRange actorRange, uint16_t actorID, 
    lcf::ChangeEquip::Operation operation, lcf::ChangeEquip::ItemIDType itemIDType, 
    lcf::ChangeEquip::Item whichItem, uint16_t itemID)
{
    assert(actorID >= RPGMAKER::MIN_ID && actorID <= RPGMAKER::MAX_NUM_CHARS);
    assert(itemID >= RPGMAKER::MIN_ID && itemID <= RPGMAKER::MAX_ID);

    auto* lcfManager = LCFManager::Get();
    assert(lcfManager);

    lcf::Character* character = lcfManager->GetDatabase().GetCharacterByID(actorID);
    assert(character);

    int16_t resultID = operation == lcf::ChangeEquip::Operation::CHANGE_EQUIPMENT ? itemID : RPGMAKER::INVALID_ID;

    switch(whichItem)
    {
        case lcf::ChangeEquip::Item::UNEQUIP_WEAPON:
            character->WeaponID = resultID;
            break;
        case lcf::ChangeEquip::Item::UNEQUIP_SHIELD:
            character->ShieldID = resultID;
            break;
        case lcf::ChangeEquip::Item::UNEQUIP_BODY:
            character->BodyID = resultID;
            break;
        case lcf::ChangeEquip::Item::UNEQUIP_HEAD:
            character->HeadID = resultID;
            break;
        case lcf::ChangeEquip::Item::UNEQUIP_ACCESSORY:
            character->AccessoryID = resultID;
            break;
        case lcf::ChangeEquip::Item::UNEQUIP_ALL:
            character->WeaponID = resultID;
            character->ShieldID = resultID;
            character->BodyID = resultID;
            character->HeadID = resultID;
            character->AccessoryID = resultID;
            break;
    }
}

// Variables
int32_t RPGMakerImpl::ControlVariables(uint16_t id)
{
    const auto* const variableManager = VariableManager::Get();
    return variableManager->GetVariable(id);
}

void RPGMakerImpl::ControlVariables(uint16_t id, int32_t value) 
{
    auto* const variableManager = VariableManager::Get();
    variableManager->SetVariable(id, value);
}

// Events
void RPGMakerImpl::SetEventLocation(uint16_t eventID, 
    lcf::SetEventLocation::LocationType locationType, uint16_t xPos, uint16_t yPos)
{
    assert((eventID >= RPGMAKER::MIN_ID && eventID <= RPGMAKER::MAX_ID) 
         || eventID == static_cast<uint16_t>(lcf::SetEventLocation::EventIDType::THIS_EVENT_ID));

    auto* lcfManager = LCFManager::Get();
    assert(lcfManager);

    lcf::Event* event = lcfManager->GetMap().GetEventByID(eventID);
    assert(event);

    // TODO: Should make sure that the event is not outside of the map.
    event->x = xPos;
    event->y = yPos;
}

uint16_t RPGMakerImpl::GetEventID(lcf::GetEventID::LocationType locationType, 
    uint16_t xPos, uint16_t yPos)
{
    auto* lcfManager = LCFManager::Get();
    assert(lcfManager);

    lcf::Event* event = lcfManager->GetMap().GetEventByPosition(xPos, yPos);
    assert(event);

    return event->GetID();
}

void RPGMakerImpl::CallEvent(lcf::CallEvent::EventType eventType, uint16_t eventID, 
    uint16_t pageID)
{
    // The only events that this function supports are the generated MAP ROM Events.
    auto* lcfManager = LCFManager::Get();
    assert(lcfManager);

    lcf::Event* event = lcfManager->GetMap().GetEventByID(eventID);
    assert(event);
    assert(event->GetEventName().find("ROM") != std::string::npos);

    lcf::EventPage* eventPage = event->GetEventPageByID(pageID);
    assert(eventPage);
    
    auto* variableManager = VariableManager::Get();
    assert(variableManager);

    int32_t byteOffset = variableManager->GetVariable(static_cast<uint16_t>(VARMAPPING::BYTE_OFFSET_ID));
    int32_t labelID = (byteOffset / 3) + 1;

    int32_t eventCommandIndex = MEMORYSIZES::MAP_ROM_HEADER_COUNT + (labelID - 1) * MEMORYSIZES::MAP_ROM_LABEL_COUNT;
    eventCommandIndex += 7;

    auto* eventCommand = eventPage->GetEventCommandByIndex(eventCommandIndex);
    assert(eventCommand);

    // Make sure that the eventCommand that we need is the correct one.
    assert(eventCommand->stringParam == "");
    assert(eventCommand->type == lcf::EventCommand::CommandType::CONTROL_VARIABLE);
    const std::vector<int32_t>& parameters = eventCommand->parameters;
    assert(parameters.size() == 7);
    assert(parameters.at(0) == 0);
    assert(parameters.at(1) == static_cast<int32_t>(VARMAPPING::READ_VAR_1));
    assert(parameters.at(2) == static_cast<int32_t>(VARMAPPING::READ_VAR_1));
    assert(parameters.at(3) == 0);
    assert(parameters.at(4) == 0);
    assert(parameters.at(6) == 0);

    int32_t packedByteValue = parameters.at(5);
    variableManager->SetVariable(static_cast<uint16_t>(VARMAPPING::READ_VAR_1), packedByteValue);

    // TODO: This assumes that we only have two READ_VAR!
    // Set the 2nd variable.
    eventCommand = eventPage->GetEventCommandByIndex(eventCommandIndex + 1);
    assert(eventCommand);

    packedByteValue = eventCommand->parameters.at(5);
    variableManager->SetVariable(static_cast<uint16_t>(VARMAPPING::READ_VAR_2), packedByteValue);

    return;
}

// Rendering
void RPGMakerImpl::ShowPicture(lcf::ShowPicture::PictureIDType pictureIDType, uint16_t pictureID, 
    lcf::ShowPicture::PosType posType, uint16_t xPos, uint16_t yPos, 
    float red /*= 1.0f*/, float green /*= 1.0f*/, float blue /*= 1.0f*/, float saturation /*= 1.0f*/)
{
    // TODO: This is for testing rendering stuff.
    uint8_t red8 = static_cast<uint8_t>(red * 255.0f);
    uint8_t green8 = static_cast<uint8_t>(green * 255.0f);
    uint8_t blue8 = static_cast<uint8_t>(blue * 255.0f);

    std::vector<uint8_t> rgba = {red8, green8, blue8, 255};

    RenderManager::Get()->PutPixel(xPos, yPos, rgba);
}

// Input
bool RPGMakerImpl::KeyInputProcessing(RPGMAKER::KeyCodes keycode)
{
    return rpgenv::InputManager::Get()->isKeyPressed(keycode);
}

};