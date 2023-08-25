#pragma once

#include <core/structure/ManagerInterface.h>
#include <core/structure/Singleton.h>

#include <cstdint>
#include <vector>


namespace rpgenv 
{

// Used to manipulate static variables, that are defined by the static variable mapping by the code generation. Any RPGMaker switch or non-static variable will not be managed by this.
class VariableManager : public Singleton<VariableManager>, public IManager
{
public:
    void Init() override;

    void SetVariable(uint16_t id, int32_t value);
    int32_t GetVariable(uint16_t id) const;

private:
    // The first variable is unused, because the variable IDs start with 1.
    std::vector<int32_t> m_StaticVariables;
};

}