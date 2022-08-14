#pragma once

#include <string>
#include <vector>

namespace lcf {

/**
 * @brief Template for serializers that read/write an entire file, which contains multiple instances of T.
 * 
 * @tparam T: The datatype you want to parse with this serializer. 
 */
template <typename T>
class MultiSerializer {
protected:
    MultiSerializer() {};

private:
    virtual std::vector<T> MultipleFromFile(std::string fileName) = 0;
    virtual void MultipleToFile(std::string fileName, std::vector<T>& elems) = 0;
};

};
