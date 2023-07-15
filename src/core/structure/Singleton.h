#pragma once

namespace rpgenv 
{

template <class T>
class Singleton
{
public:
    Singleton()
    {
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
        return static_cast<T*>(s_Instance);
    }

private:
    static Singleton<T>* s_Instance;
};

template<class T>
Singleton<T>* Singleton<T>::s_Instance = nullptr;

};