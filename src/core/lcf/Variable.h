#pragma once

#include "Filemode.h"

#include <string>

namespace tinyxml2 { class XMLDocument; }

// TODO: Variable is basically the same as Switch, Can I combine them?
class Variable {
public:
    Variable(std::string fileName, FILE_MODE fileMode);
    Variable(const Variable& other) = delete;
    Variable(Variable&& other) = delete;
    ~Variable();
    
    Variable& operator=(const Variable& other) = delete;
    Variable& operator=(Variable&& other) = delete;

    std::string getName();
    void setName(std::string val);

    uint16_t getID();
    void setID(uint16_t val);

    bool getValue();
    void setValue(bool val);

private:
    tinyxml2::XMLDocument* file;
    std::string fileName;

    std::string name;
    uint16_t id;
    bool value; 
};