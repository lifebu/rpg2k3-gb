#include "VariableSerializer.h"

#include <iostream>

#include "thirdparty/tinyxml2/tinyxml2.h"


namespace lcf {

Variable VariableSerializer::FromFile(std::string fileName) {
    std::string name = "";
    uint16_t id = 1;
    
    auto file = tinyxml2::XMLDocument(fileName);
    if (file.Error()) {
        std::cout << file.ErrorStr() << std::endl;
        return Variable(name, id);
    }

    auto* nameElem = file.TraverseElement("/Variable/name")->FirstChild()->ToText();
    name = nameElem.Value();
    id = file.RootElement()->UnsignedAttribute("id");

    return Variable(name, id);
}

};
