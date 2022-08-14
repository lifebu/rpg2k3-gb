#pragma once

#include <string>

/**
 * @brief Template for serializers that are embedded in FullSerializers (allows for code to be re-used).
 * 
 * @tparam T: The datatype you want to parse with this serializer. 
 */
template <typename T>
class PartialSerializer {
protected:
    PartialSerializer() {};

private:
    virtual T FromFile(std::unique_ptr<tinyxml2::XMLDocument>& doc) = 0;
    virtual std::unique_ptr<tinyxml2::XMLDocument> ToFile(T& elem) = 0;
};

