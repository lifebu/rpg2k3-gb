#pragma once

#include <utility>

namespace emu
{

// Responsible for updating the Timer and Divider.
class Timer
{

public:
    static void Init();
    static void Update();
};

};