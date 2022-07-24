#include "SwitchSerializer.h"

#include "Templates.h"

#include "src/core/utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>


namespace lcf {

Switch SwitchSerializer::FromFile(std::string fileName) {
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

    return Switch(id, name);
}

std::unique_ptr<tinyxml2::XMLDocument> SwitchSerializer::ToFile(Switch& elem) {
    auto switchTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::SWITCH);

    // Set switch ID
    switchTempl->RootElement()->SetAttribute("id", generateID(elem.getID()).c_str());

    // Change switch name
    auto* nameElem = switchTempl->TraverseElement("/Switch/name")->FirstChild()->ToText();
    nameElem->SetValue(elem.getName().c_str());

    return switchTempl;
}

};
