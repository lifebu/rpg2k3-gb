#pragma once

#include <core/def/VarMapping.h>
#include <core/structure/ManagerInterface.h>
#include <core/structure/Singleton.h>

#include <array>
#include <cstdint>
#include <vector>


namespace rpgenv 
{

// Used to manipulate static variables, that are defined by the static variable mapping by the code generation. Any RPGMaker switch or non-static variable will not be managed by this.
class VariableManager : public Singleton<VariableManager>, public IManager
{
public:
    void SetVariable(uint16_t id, int32_t value);
    int32_t GetVariable(uint16_t id) const;

private:
    std::array<int32_t, static_cast<std::size_t>(VARMAPPING::COUNT)> m_StaticVariables;
};

}