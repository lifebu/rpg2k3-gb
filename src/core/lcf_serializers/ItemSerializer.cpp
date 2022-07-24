#include "ItemSerializer.h"

#include "Templates.h"

#include "src/core/utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"

#include <iostream>
#include <tuple>


namespace lcf {

Item ItemSerializer::FromFile(std::string fileName) {
    /*
    std::string name = "";
    uint16_t id = 1;
    
    auto file = tinyxml2::XMLDocument(fileName.c_str());
    if (file.Error()) {
        std::cout << file.ErrorStr() << std::endl;
        return Item(id, name);
    }

    auto* nameElem = file.TraverseElement("/Switch/name")->FirstChild()->ToText();
    name = nameElem->Value();
    id = file.RootElement()->UnsignedAttribute("id");
    */

    return Item(0, "name", ItemType::WEAPON);
}

// Generate the local IDs required for the correct type IDs of the item.
uint16_t constexpr getLocalID(int id) {
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


std::unique_ptr<tinyxml2::XMLDocument> ItemSerializer::ToFile(Item& elem) {
    auto itemTempl = std::make_unique<tinyxml2::XMLDocument>(TEMPLATES::ITEM);

    // Set switch ID
    itemTempl->RootElement()->SetAttribute("id", generateID(elem.getID()).c_str());

    // Change item Name: E.g. WPN0001, BODY0012
    uint16_t localID = getLocalID(elem.getID());
    auto* name = itemTempl->TraverseElement("/Item/name")->FirstChild()->ToText();
    name->SetValue((RPGMAKER::ITEM_NAMES[elem.getType()] + generateID(localID)).c_str());

    // Change item type
    auto* type = itemTempl->TraverseElement("/Item/type")->FirstChild()->ToText();
    type->SetValue(std::to_string(elem.getType()).c_str());

    return itemTempl;
}

};
