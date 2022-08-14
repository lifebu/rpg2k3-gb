#pragma once

#include <string>


namespace lcf {

enum ItemType {
    WEAPON = 1,
    SHIELD = 2,
    BODY = 3,
    HEAD = 4,
    ACCESSORY = 5
};

class Item {
public:
    Item(uint16_t id, std::string name, ItemType type);

    uint16_t getID();
    void setID(uint16_t val);

    std::string getName();
    void setName(std::string val);

    ItemType getType();
    void setType(ItemType val);

private:
    uint16_t id;
    std::string name;
    ItemType type;
};

};