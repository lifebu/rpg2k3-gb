#pragma once

#include "core/pch.h"
#include <functional>
#include <map>
#include <utility>

namespace rpgenv 
{

template <class T>
class StateMachine
{
public:
    void Init(T startState)
    {
        m_CurrState = startState;
    }

    void ChangeState(T newState)
    {
        T oldState = m_CurrState;
        m_CurrState = newState;

        if(oldState != newState)
        {
            auto foundIt = m_Transitions.find(std::make_pair(oldState, newState));
            if(foundIt != m_Transitions.end())
            {
                foundIt->second();
            }
        }
    }

    void Update()
    {
        if(m_AnyUpdateFunction)
            m_AnyUpdateFunction();

        auto foundIt = m_UpdateFunctions.find(m_CurrState);
        assert(foundIt != m_UpdateFunctions.end());

        foundIt->second();
    }

    bool IsInState(T newState)
    {
        return m_CurrState == newState;
    }

protected:
    void SetAnyUpdateFunction(std::function<void()> func)
    {
        m_AnyUpdateFunction = func;
    }

    void AddUpdateFunction(T state, std::function<void()> func)
    {
        m_UpdateFunctions[state] = func;
    }

    void AddTransition(T start, T end, std::function<void()> func)
    {
        m_Transitions[std::make_pair(start, end)] = func;
    }

private:
    T m_CurrState;
    // Called regardless of what state we are in.
    std::function<void()> m_AnyUpdateFunction;                      
    std::map<T, std::function<void()>> m_UpdateFunctions;
    std::map<std::pair<T, T>, std::function<void()>> m_Transitions;
};

};
