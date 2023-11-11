#pragma once

#include "core/pch.h"

template <class T>
class Singleton
{
public:
    Singleton()
    {
        assert(s_Instance == nullptr);
        s_Instance = this;
    }

    virtual ~Singleton()
    {
        s_Instance = nullptr;
    }

    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    static T* Get()
    {
        assert(s_Instance != nullptr);
        return static_cast<T*>(s_Instance);
    }

private:
    static Singleton<T>* s_Instance;
};

template<class T>
Singleton<T>* Singleton<T>::s_Instance = nullptr;