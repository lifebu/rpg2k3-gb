#include "DatabaseSerializer.h"

#include "Templates.h"
#include "CommonEventSerializer.h"

#include "utilities/RPGHelper.h"
#include "structure/Logger.h"

#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>

namespace lcf 
{

Database DatabaseSerializer::FromFile(std::string fileName) 
{
    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) 
    {
        core::Logger::Get()->Log(file.ErrorStr(), core::LogLevel::ERROR);
        return Database();
    }

    Database database = Database();

    // Switches
    auto* currentSwitch = file.TraverseElement("/LDB/Database/switches/Switch");
    while(currentSwitch)
    {
        Switch newSwitch = SwitchFromFileImpl(currentSwitch);
        database.addSwitch(newSwitch);
        currentSwitch = currentSwitch->NextSiblingElement();
    }

    // Variables
    auto* currentVariable = file.TraverseElement("/LDB/Database/variables/Variable");
    while(currentVariable)
    {
        Variable newVariable = VariableFromFileImpl(currentVariable);
        database.addVariable(newVariable);
        currentVariable = currentVariable->NextSiblingElement();
    }

    // Items
    auto* currentItem = file.TraverseElement("/LDB/Database/items/Item");
    while(currentItem)
    {
        Item newItem = ItemFromFileImpl(currentItem);
        database.addItem(newItem);
        currentItem = currentItem->NextSiblingElement();
    }

    // Characters
    auto* currentCharacter = file.TraverseElement("/LDB/Database/actors/Actor");
    while(currentCharacter)
    {
        Character newCharacter = CharacterFromFileImpl(currentCharacter);
        database.addCharacter(newCharacter);
        currentCharacter = currentCharacter->NextSiblingElement();
    }

    // Common Events
    auto* currentCommand = file.TraverseElement("/LDB/Database/commonevents/CommonEvent");
    while(currentCommand)
    {
        CommonEvent newCommonEvent = CommonEventSerializer::FromFileImpl(currentCommand);
        database.addCommonEvent(newCommonEvent);
        currentCommand = currentCommand->NextSiblingElement();
    }

    return database;
}

void DatabaseSerializer::ToFile(std::string fileName, Database& database) 
{
    tinyxml2::XMLDocument databaseTempl(TEMPLATES::DATABASE);
    tinyxml2::XMLDocument switchTempl(TEMPLATES::SWITCH);
    tinyxml2::XMLDocument variableTempl(TEMPLATES::VARIABLE);
    tinyxml2::XMLDocument itemTempl(TEMPLATES::ITEM);
    tinyxml2::XMLDocument characterTempl(TEMPLATES::CHARACTER);
    tinyxml2::XMLDocument commonEventTempl(TEMPLATES::COMMON_EVENT);

    // Switches
    for(auto& currentSwitch : database.switches) 
    {
        auto* switchElem = switchTempl.TraverseElement("/Switch");
        SwitchToFileImpl(currentSwitch, switchElem);

        switchElem->DeepCloneInsertBack(&databaseTempl, databaseTempl.TraverseElement("/LDB/Database/switches"));
    }

    // Variables
    for(auto& variable : database.variables) 
    {
        auto* variableElem = variableTempl.TraverseElement("/Variable");
        VariableToFileImpl(variable, variableElem);

        variableElem->DeepCloneInsertBack(&databaseTempl, databaseTempl.TraverseElement("/LDB/Database/variables"));
    }

    // Items
    for(auto& item : database.items) 
    {
        auto* itemElem = itemTempl.TraverseElement("/Item");
        ItemToFileImpl(item, itemElem);

        itemElem->DeepCloneInsertBack(&databaseTempl, databaseTempl.TraverseElement("/LDB/Database/items"));
    }

    // Characters
    for(auto& character : database.characters) 
    {
        auto* characterElem = characterTempl.TraverseElement("/Actor");
        CharacterToFileImpl(character, characterElem);

        characterElem->DeepCloneInsertBack(&databaseTempl, databaseTempl.TraverseElement("/LDB/Database/actors"));
    }

    // Common Events
    for(auto& commonEvent : database.commonEvents) 
    {
        auto* commoneventElem = commonEventTempl.TraverseElement("/CommonEvent");
        CommonEventSerializer::ToFileImpl(commonEvent, &databaseTempl, commoneventElem);

        commoneventElem->DeepCloneInsertBack(&databaseTempl, databaseTempl.TraverseElement("/LDB/Database/commonevents"));
    }

    // TODO: compact could be an argument?
    bool compactMode = false;
    databaseTempl.SaveFile(fileName.c_str(), compactMode);
    if (databaseTempl.Error()) 
    {
        core::Logger::Get()->Log(databaseTempl.ErrorStr(), core::LogLevel::ERROR);
    }
}

Switch DatabaseSerializer::SwitchFromFileImpl(tinyxml2::XMLElement* switchElem)
{
    // Get Switch ID
    uint16_t id = switchElem->IntAttribute("id");

    // Get Switch Name.
    auto* nameElem = switchElem->TraverseElement("/name")->FirstChild()->ToText();
    std::string name = (nameElem == nullptr) ? "" : nameElem->Value();

    return Switch(id, name);
}

void DatabaseSerializer::SwitchToFileImpl(const Switch& elem, tinyxml2::XMLElement* switchElem)
{
    // Set Switch ID
    switchElem->SetAttribute("id", generateID(elem.id).c_str());

    // Set Switch Name
    auto* nameElem = switchElem->TraverseElement("/name")->FirstChild()->ToText();
    nameElem->SetValue(elem.name.c_str()); 
}

Variable DatabaseSerializer::VariableFromFileImpl(tinyxml2::XMLElement* variableElem)
{
    // Get Variable ID
    uint16_t id = variableElem->IntAttribute("id");

    // Get Variable Name.
    auto* nameElem = variableElem->TraverseElement("/name")->FirstChild()->ToText();
    std::string name = (nameElem == nullptr) ? "" : nameElem->Value();

    return Variable(id, name);
}

void DatabaseSerializer::VariableToFileImpl(const Variable& elem, tinyxml2::XMLElement* variableElem)
{
    // Set Variable ID
    variableElem->SetAttribute("id", generateID(elem.id).c_str());

    // Set Variable Name
    auto* nameElem = variableElem->TraverseElement("/name")->FirstChild()->ToText();
    nameElem->SetValue(elem.name.c_str()); 
}

Character DatabaseSerializer::CharacterFromFileImpl(tinyxml2::XMLElement* characterElem)
{
    // Get Character ID
    uint16_t id = characterElem->IntAttribute("id");

    // Get Character Name.
    auto* nameElem = characterElem->TraverseElement("/name")->FirstChild()->ToText();
    std::string name = (nameElem == nullptr) ? "" : nameElem->Value();

    // TODO: Do I need to serialize character stats and items? 

    return Character(id, name);
}

void DatabaseSerializer::CharacterToFileImpl(const Character& elem, tinyxml2::XMLElement* characterElem)
{
    // Set Character ID
    characterElem->SetAttribute("id", generateID(elem.id).c_str());

    // Set Character Name
    auto* nameElem = characterElem->TraverseElement("/name")->FirstChild()->ToText();
    nameElem->SetValue(elem.name.c_str());

    // TODO: Do I need to serialize character stats and items? 
}

Item DatabaseSerializer::ItemFromFileImpl(tinyxml2::XMLElement* itemElem)
{
    // Get Item ID
    uint16_t id = itemElem->IntAttribute("id");

    // Get Item Name.
    auto* nameElem = itemElem->TraverseElement("/name")->FirstChild()->ToText();
    std::string name = (nameElem == nullptr) ? "" : nameElem->Value();
    // TODO: make a constant out this somewhere in the def
    const static int ID_STRING_LENGTH = 4;
    // Remove the id from the name
    name.erase(name.end() - ID_STRING_LENGTH, name.end());

    // Get Item Type
    auto* typeElem = itemElem->TraverseElement("/type")->FirstChild();
    Item::ItemType type = static_cast<Item::ItemType>(std::stoi(typeElem->Value()));

    return Item(id, name, type);
}

void DatabaseSerializer::ItemToFileImpl(const Item& elem, tinyxml2::XMLElement* itemElem)
{
    // Set Item ID
    itemElem->SetAttribute("id", generateID(elem.id).c_str());

    // Set Item Name: E.g. WPN0001, BODY0012
    uint16_t localID = getLocalItemID(elem.id);
    auto* nameElem = itemElem->TraverseElement("/name")->FirstChild()->ToText();
    nameElem->SetValue((RPGMAKER::ITEM_NAMES[elem.type] + generateID(localID)).c_str());

    // Set Item Type
    auto* typeElem = itemElem->TraverseElement("/type")->FirstChild();
    typeElem->SetValue(std::to_string(elem.type).c_str());
}

uint16_t constexpr DatabaseSerializer::getLocalItemID(int id)
{
    // TODO: the lower and upper bounds should be calculated using MEMORYSIZES::NUM_OF_*. makes this configureable!
    // TODO: Could probably do this waaaay better!
    if(id >= 1 && id <= 2048) {
        return id;
    
    } else if (id > 2048 && id <= 4096) {
        return id - 2048;
    
    } else if (id > 4096 && id <= 6144) {
        return id - 4096;
    
    } else if (id > 6144 && id <= 8192) {
        return id - 6144;
    
    } else if (id > 8192 && id <= 9216) {
        return id - 8192;
    
    } else {
        return 0;
    }  
}

};
