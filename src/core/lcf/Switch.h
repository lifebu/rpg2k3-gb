#pragma once

#include <string>


namespace lcf {

class Switch {
public:
    Switch(std::string name, uint16_t id, bool value = false);

    std::string getName();
    void setName(std::string val);

    uint16_t getID();
    void setID(uint16_t val);

    bool getValue();
    void setValue(bool val);

private:
    std::string name;
    uint16_t id;
    bool value;
};

};