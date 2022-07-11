#pragma once

#include "Filemode.h"

#include <string>

namespace tinyxml2 { class XMLDocument; }

// TODO: Variable is basically the same as Switch, Can I combine them?
class Switch {
public:
    Switch(std::string fileName, FILE_MODE fileMode);
    Switch(const Switch& other) = delete;
    Switch(Switch&& other) = delete;
    ~Switch();
    
    Switch& operator=(const Switch& other) = delete;
    Switch& operator=(Switch&& other) = delete;

    std::string getName();
    void setName(std::string val);

    uint16_t getID();
    void setID(uint16_t val);

    int32_t getValue();
    void setValue(int32_t val);

private:
    tinyxml2::XMLDocument* file;
    std::string fileName;

    std::string name;
    uint16_t id;
    int32_t value; 
};