#include "VariableManager.h"

#include <limits>

#include "core/utilities/RPGHelper.h"

namespace rpgenv
{

void VariableManager::SetVariable(uint16_t id, int32_t value)
{
    assert(id > 0 && id < m_StaticVariables.size());
    m_StaticVariables.at(getIndexFromID(id)) = value;
}

int32_t VariableManager::GetVariable(uint16_t id) const
{
    assert(id > 0 && id < m_StaticVariables.size());
    return m_StaticVariables.at(getIndexFromID(id));
}

};
