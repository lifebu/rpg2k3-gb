#pragma once


#include <string>


namespace lcf {

class Variable {
public:
    Variable(uint16_t id, std::string name, int32_t value = 0);

    std::string getName();
    void setName(std::string val);

    uint16_t getID();
    void setID(uint16_t val);

    int32_t getValue();
    void setValue(int32_t val);

private:
    std::string name;
    uint16_t id;
    int32_t value;
};

};