#pragma once

#include <string>

/**
 * @brief Template for serializers that are embedded in MultiSerializers (allows for code to be re-used).
 * 
 * @tparam T: The datatype you want to parse with this serializer. 
 */
template <typename T>
class PartialMultiSerializer {
protected:
    PartialMultiSerializer() {};

private:
    virtual std::vector<T> MultipleFromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) = 0;
    virtual std::unique_ptr<tinyxml2::XMLDocument> MultipleToFile(std::vector<T>& elems) = 0;
};

