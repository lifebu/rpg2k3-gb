#pragma once

#include <string>
#include <cstdint>

namespace lcf {


class Item {
    friend class DatabaseSerializer;

public:
    enum ItemType {
        WEAPON = 1,
        SHIELD = 2,
        BODY = 3,
        HEAD = 4,
        ACCESSORY = 5
    };

    Item(const uint16_t id, const std::string name, const ItemType type);

    uint16_t GetID() const;

private:
    // static
    const uint16_t id;
    const std::string name;
    const ItemType type;

public:
    // runtime
    int amount = 0;
};

};