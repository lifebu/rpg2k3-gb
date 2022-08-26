#pragma once

#include <string>


namespace lcf {


class Item {
    friend class ItemSerializer;

public:
    enum ItemType {
        WEAPON = 1,
        SHIELD = 2,
        BODY = 3,
        HEAD = 4,
        ACCESSORY = 5
    };

    Item(const uint16_t id, const std::string name, const ItemType type);

private:
    const uint16_t id;
    const std::string name;
    const ItemType type;
};

};