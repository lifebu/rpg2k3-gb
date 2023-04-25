#pragma once

#include <string>


namespace lcf {

class MapInfo {
    friend class MapTreeSerializer;

public:
    MapInfo(const uint16_t id, const std::string name);

private:
    const uint16_t id;
    const std::string name;
};

};