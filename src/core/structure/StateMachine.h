#pragma once

#include <functional>
#include <map>
#include <cassert>

namespace rpgenv 
{

template <class T>
class StateMachine
{
public:
    void ChangeState(T newState)
    {
        m_CurrState = newState;
    }

    void Update()
    {
        auto foundIt = m_UpdateFunctions.find(m_CurrState);
        assert(foundIt != m_UpdateFunctions.end());

        foundIt->second();
    }

protected:
    void AddUpdateFunction(T state, std::function<void()> func)
    {
        m_UpdateFunctions[state] = func;
    }


private:
    T m_CurrState;
    std::map<T, std::function<void()>> m_UpdateFunctions;
};

};
