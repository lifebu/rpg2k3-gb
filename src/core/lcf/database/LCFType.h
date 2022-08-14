#pragma once

#include <string>


namespace lcf {

template<typename T>
class LCFType {
    friend class SwitchSerializer;
    friend class VariableSerializer;
protected:
    LCFType(uint16_t id, std::string name, T value);

public:
    LCFType() = delete;

    T getValue();
    void setValue(T val);

    const uint16_t id;
    const std::string name;

private:
    T value;
};

class Switch : public LCFType<bool> {
    friend class SwitchSerializer;
public:
    Switch(uint16_t id, std::string name, bool value = false);
};

class Variable : public LCFType<int32_t> {
    friend class VariableSerializer;
public:
    Variable(uint16_t id, std::string name, int32_t value = 0);
};

};