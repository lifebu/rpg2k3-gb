#include "VariableSerializer.h"

#include "Templates.h"

#include "src/core/utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>

namespace lcf {

Variable VariableSerializer::FromFile(std::string fileName) {
    std::string name = "";
    uint16_t id = 1;
    
    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) {
        std::cout << file.ErrorStr() << std::endl;
        return Variable(id, name);
    }

    auto* nameElem = file.TraverseElement("/Variable/name")->FirstChild()->ToText();
    name = nameElem->Value();
    id = file.RootElement()->UnsignedAttribute("id");

    return Variable(id, name);
}

std::unique_ptr<tinyxml2::XMLDocument> VariableSerializer::ToFile(Variable& elem) {
    auto variableTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::VARIABLE);

    // Set variable ID
    variableTempl->RootElement()->SetAttribute("id", generateID(elem.getID()).c_str());

    // Change variable name
    auto* nameElem = variableTempl->TraverseElement("/Variable/name")->FirstChild()->ToText();
    nameElem->SetValue(elem.getName().c_str());

    return variableTempl;
}

};
