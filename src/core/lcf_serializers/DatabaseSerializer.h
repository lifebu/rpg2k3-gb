#pragma once

#include <string>

#include "core/lcf/Database.h"


namespace tinyxml2 {class XMLDocument; class XMLElement;};

namespace lcf 
{

class DatabaseSerializer
{
public:
    static Database FromFile(std::string fileName);
    static void ToFile(std::string fileName, Database& database);

private:
    static Switch SwitchFromFileImpl(tinyxml2::XMLElement* switchElem);
    static void SwitchToFileImpl(const Switch& elem, tinyxml2::XMLElement* switchElem);

    static Variable VariableFromFileImpl(tinyxml2::XMLElement* variableElem);
    static void VariableToFileImpl(const Variable& elem, tinyxml2::XMLElement* variableElem);

    static Character CharacterFromFileImpl(tinyxml2::XMLElement* characterElem);
    static void CharacterToFileImpl(const Character& elem, tinyxml2::XMLElement* characterElem);

    static Item ItemFromFileImpl(tinyxml2::XMLElement* itemElem);
    static void ItemToFileImpl(const Item& elem, tinyxml2::XMLElement* itemElem);

    static uint16_t constexpr getLocalItemID(int id);
};

};