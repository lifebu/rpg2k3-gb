#pragma once

#include <string>


namespace lcf {

class Character {
public:
    Character(uint16_t id, std::string name);

    uint16_t getID();
    void setID(uint16_t val);

    std::string getName();
    void setName(std::string val);

private:
    uint16_t id;
    std::string name;

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
};

};