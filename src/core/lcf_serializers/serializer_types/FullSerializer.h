#pragma once

#include <string>

/**
 * @brief Template for serializers that read/write an entire file.
 * 
 * @tparam T: The datatype you want to parse with this serializer. 
 */
template <typename T>
class FullSerializer {
protected:
    FullSerializer() {};

private:
    virtual T FromFile(std::string fileName) = 0;
    virtual void ToFile(std::string fileName, T& elem) = 0;
};

