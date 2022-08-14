#pragma once

#include "lcf_serializers/serializer_types/PartialSerializer.h"
#include "lcf/database/LCFType.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {

template<typename T>
class LCFTypeSerializer : PartialSerializer<T> {
    // TODO: Some way to enforce that the T we use is of type LCFType. Could use C++20 Concepts.
    //static_assert(std::is_base_of_v<LCFType, T>);

public:
    T FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) override;
    std::unique_ptr<tinyxml2::XMLDocument> ToFile(T& elem) override;

protected:
    LCFTypeSerializer() {};

    std::string namePath;
    std::string templatePath;
};


class VariableSerializer : public LCFTypeSerializer<Variable> {
public:
    VariableSerializer();
};


class SwitchSerializer : public LCFTypeSerializer<Switch> {
public:
    SwitchSerializer();
};

};