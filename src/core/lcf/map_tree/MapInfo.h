#pragma once

#include <string>


namespace lcf {

class MapInfo {
public:
    MapInfo(uint16_t id, std::string name);

    uint16_t getID();
    void setID(uint16_t val);

    std::string getName();
    void setName(std::string val);

private:
    uint16_t id;
    std::string name;
};

};