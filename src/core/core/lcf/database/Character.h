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
    uint32_t exp = 30;
    uint16_t maxHP = 50;
    uint16_t maxMP = 70;
    uint16_t attack = 90;
    uint16_t defense = 110;
    uint16_t mind = 130;
    uint16_t agility = 150;

    // items
    uint16_t WeaponID = 170;
    uint16_t ShieldID = 190;
    uint16_t BodyID = 210;
    uint16_t HeadID = 230;
    uint16_t AccessoryID = 250;

    // party
    bool isInParty = false;

private:
    const std::string name;
};

};