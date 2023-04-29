#pragma once


namespace rpgenv 
{

class InputManager
{
private:
    InputManager() = default;

public:
    static InputManager* Get();

    void Init();
    void Shutdown();
};

}