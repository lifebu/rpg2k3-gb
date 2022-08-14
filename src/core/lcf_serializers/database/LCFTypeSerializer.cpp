#include "LCFTypeSerializer.h"

#include "lcf_serializers/Templates.h"

#include "utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>

namespace lcf {

// LCFTypeSerializer
template<typename T>
T LCFTypeSerializer<T>::FromFile(std::string fileName) {
    std::string name = "";
    uint16_t id = 1;
    
    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) {
        std::cout << file.ErrorStr() << std::endl;
        return T(id, name);
    }

    auto* nameElem = file.TraverseElement(namePath.c_str())->FirstChild()->ToText();
    name = nameElem->Value();
    id = file.RootElement()->UnsignedAttribute("id");

    return T(id, name);
}

template<typename T>
std::unique_ptr<tinyxml2::XMLDocument> LCFTypeSerializer<T>::ToFile(T& elem) {
    auto variableTempl = std::make_unique<tinyxml2::XMLDocument>(templatePath.c_str());

    // Set variable ID
    variableTempl->RootElement()->SetAttribute("id", generateID(elem.id).c_str());

    // Change variable name
    auto* nameElem = variableTempl->TraverseElement(namePath.c_str())->FirstChild()->ToText();
    nameElem->SetValue(elem.name.c_str());

    return variableTempl;
}

// Variable Serializer
VariableSerializer::VariableSerializer() {
    namePath = "/Variable/name";
    templatePath = TEMPLATES::VARIABLE;
}

// Switch Serializer
SwitchSerializer::SwitchSerializer() {
    namePath = "/Switch/name";
    templatePath = TEMPLATES::SWITCH;
}

};
