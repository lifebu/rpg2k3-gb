#include "VariableManager.h"

#include <core/def/VarMapping.h>

#include <limits>

namespace rpgenv
{

void VariableManager::Init() 
{
    m_StaticVariables.resize(static_cast<std::size_t>(VARMAPPING::COUNT) + 1);
    m_StaticVariables.at(0) = std::numeric_limits<int32_t>::lowest();
}

void VariableManager::SetVariable(uint16_t id, int32_t value)
{
    assert(id > 0 && id < m_StaticVariables.size());
    m_StaticVariables.at(id) = value;
}

int32_t VariableManager::GetVariable(uint16_t id) const
{
    assert(id > 0 && id < m_StaticVariables.size());
    return m_StaticVariables.at(id);
}

};
