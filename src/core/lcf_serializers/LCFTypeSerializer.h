#pragma once

#include "Serializer.h"
#include "src/core/lcf/LCFType.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; };


namespace lcf {
// IF I don't need friend class for the data => can create a class for Variable and Switch serializer to not have duplicate code.

template<typename T>
class LCFTypeSerializer : Serializer<T> {
    // TODO: Some way to enforce that the T we use is of type LCFType. Can use C++20 Concepts.
    //static_assert(std::is_base_of_v<LCFType, T>);

public:
    T FromFile(std::string fileName) override;
    std::unique_ptr<tinyxml2::XMLDocument> ToFile(T& elem) override;

protected:
    LCFTypeSerializer() {};

private:
    // Empty private definitions we do not need.
    void ToFile(std::string fileName, T& elem) override {};
    std::vector<T> MultipleFromFile(std::string fileName) override {return std::vector<T>();};
    void MultipleToFile(std::string fileName, std::vector<T>& elems) override {};
    T FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) override {return T(0, "");};
    std::vector<T> MultipleFromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) override {return std::vector<T>();};
    std::unique_ptr<tinyxml2::XMLDocument> MultipleToFile(std::vector<T>& elems) override { return nullptr;};

protected:
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