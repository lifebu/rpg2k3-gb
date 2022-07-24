#pragma once

#include <string>


namespace lcf {

class Switch {
public:
    Switch(uint16_t id, std::string name, bool value = false);

    uint16_t getID();
    void setID(uint16_t val);

    std::string getName();
    void setName(std::string val);

    bool getValue();
    void setValue(bool val);

private:
    uint16_t id;
    std::string name;
    bool value;
};

};