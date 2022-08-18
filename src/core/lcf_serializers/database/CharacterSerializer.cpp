#include "CharacterSerializer.h"

#include "lcf_serializers/Templates.h"

#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>


namespace lcf {

CharacterSerializer::CharacterSerializer() {}

Character CharacterSerializer::FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) {
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
