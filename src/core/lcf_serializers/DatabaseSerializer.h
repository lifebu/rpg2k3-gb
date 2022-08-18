#pragma once

#include "../lcf_serializers/serializer_types/FullSerializer.h"
#include "../lcf/Database.h"

#include <string>


namespace lcf {

class DatabaseSerializer : FullSerializer<Database> {

public:
    DatabaseSerializer();

    Database FromFile(std::string fileName) override;
    void ToFile(std::string fileName, Database& database) override;
};

};