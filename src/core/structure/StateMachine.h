#pragma once

#include <cassert>
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
        auto foundIt = m_UpdateFunctions.find(m_CurrState);
        assert(foundIt != m_UpdateFunctions.end());

        foundIt->second();
    }

    bool IsInState(T newState)
    {
        return m_CurrState == newState;
    }

protected:
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
    std::map<T, std::function<void()>> m_UpdateFunctions;
    std::map<std::pair<T, T>, std::function<void()>> m_Transitions;
};

};
