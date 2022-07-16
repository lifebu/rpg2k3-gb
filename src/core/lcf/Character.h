#pragma once

#include "Filemode.h"

#include <string>
#include <vector>

namespace tinyxml2 { class XMLDocument; }


class Character {
public:
    Character(std::string fileName, FILE_MODE fileMode);
    Character(const Character& other) = delete;
    Character(Character&& other) = delete;
    ~Character();
    
    Character& operator=(const Character& other) = delete;
    Character& operator=(Character&& other) = delete;

private:
    tinyxml2::XMLDocument* file;
    std::string fileName;

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