#pragma once

// TODO: Better includes with having "core" as an include (CMake File!)
#include "../lcf/Variable.h"

#include <string>


namespace lcf {

class VariableSerializer {
public:
    VariableSerializer() = delete;

    static Variable FromFile(std::string fileName);
};

};