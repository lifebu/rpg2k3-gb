#include "CharacterSerializer.h"

#include "Templates.h"

#include "src/core/utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>


namespace lcf {

Character CharacterSerializer::FromFile(std::string fileName) {
    /*
    std::string name = "";
    uint16_t id = 1;
    
    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) {
        std::cout << file.ErrorStr() << std::endl;
        return Switch(id, name);
    }

    auto* nameElem = file.TraverseElement("/Switch/name")->FirstChild()->ToText();
    name = nameElem->Value();
    id = file.RootElement()->UnsignedAttribute("id");
    */

    return Character(0, "name");
}

std::unique_ptr<tinyxml2::XMLDocument> CharacterSerializer::ToFile(Character& elem) {
    auto charTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::CHARACTER);

    // Set character ID
    charTempl->RootElement()->SetAttribute("id", generateID(elem.getID()).c_str());

    // Change character name
    auto* nameElem = charTempl->TraverseElement("/Actor/name")->FirstChild()->ToText();
    nameElem->SetValue(elem.getName().c_str());

    return charTempl;
}

};
