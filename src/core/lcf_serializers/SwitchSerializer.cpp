#include "SwitchSerializer.h"

#include <iostream>

#include "thirdparty/tinyxml2/tinyxml2.h"


namespace lcf {

Switch SwitchSerializer::FromFile(std::string fileName) {
    std::string name = "";
    uint16_t id = 1;
    
    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) {
        std::cout << file.ErrorStr() << std::endl;
        return Switch(name, id);
    }

    auto* nameElem = file.TraverseElement("/Switch/name")->FirstChild()->ToText();
    name = nameElem->Value();
    id = file.RootElement()->UnsignedAttribute("id");

    return Switch(name, id);
}

};
