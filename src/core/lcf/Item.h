#pragma once

#include "Filemode.h"

#include <string>
#include <vector>

namespace tinyxml2 { class XMLDocument; }

enum ItemType {
    WEAPON = 1,
    SHIELD = 2,
    BODY = 3,
    HEAD = 4,
    ACCESSORY = 5
};

class Item {
public:
    Item(std::string fileName, FILE_MODE fileMode);
    Item(const Item& other) = delete;
    Item(Item&& other) = delete;
    ~Item();
    
    Item& operator=(const Item& other) = delete;
    Item& operator=(Item&& other) = delete;

private:
    tinyxml2::XMLDocument* file;
    std::string fileName;

    uint16_t id;
    std::string name;
    ItemType type;
};