#pragma once

#include "../lcf_serializers/serializer_types/FullSerializer.h"
#include "../lcf/Map.h"

#include <string>


namespace lcf {

class MapSerializer : FullSerializer<Map> {

public:
    MapSerializer();

    Map FromFile(std::string fileName) override;
    void ToFile(std::string fileName, Map& map) override;
};

};