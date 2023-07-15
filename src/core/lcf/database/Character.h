#pragma once

#include <string>
#include <cstdint>

namespace lcf {

class Character {
    friend class DatabaseSerializer;

public:
    Character(const uint16_t id, const std::string name);

public:
    const uint16_t id;

    // stats
    uint32_t exp;
    uint16_t maxHP;
    uint16_t maxMP;
    uint16_t attack;
    uint16_t defense;
    uint16_t mind;
    uint16_t agility;

    // items
    uint16_t WeaponID;
    uint16_t ShieldID;
    uint16_t BodyID;
    uint16_t HeadID;
    uint16_t AccessoryID;

private:
    const std::string name;
};

};