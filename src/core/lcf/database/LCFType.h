#pragma once

#include <string>


namespace lcf {

template<typename T>
class LCFType {
    friend class SwitchSerializer;
    friend class VariableSerializer;

public: 
    LCFType() = delete;

protected:
    LCFType(const uint16_t id, const std::string name, const T value);

public:
    const uint16_t id;
    const std::string name;
    T value;
};

class Switch : public LCFType<bool> {
    friend class SwitchSerializer;
public:
    Switch(const uint16_t id, const std::string name, const bool value = false);
};

class Variable : public LCFType<int32_t> {
    friend class VariableSerializer;
public:
    Variable(const uint16_t id, const std::string name, const int32_t value = 0);
};

};