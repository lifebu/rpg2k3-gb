#pragma once

#include "../lcf_serializers/serializer_types/FullSerializer.h"
#include "../lcf/MapTree.h"

#include <string>


namespace lcf {

class MapTreeSerializer : FullSerializer<MapTree> {

public:
    MapTreeSerializer();

    MapTree FromFile(std::string fileName) override;
    void ToFile(std::string fileName, MapTree& mapTree) override;
};

};