#pragma once

// TODO: Better includes with having "core" as an include (CMake File!)
#include "../lcf/Switch.h"

#include <string>


namespace lcf {

class SwitchSerializer {
public:
    SwitchSerializer() = delete;

    static Switch FromFile(std::string fileName);
};

};