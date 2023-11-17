#include "GBFile.h"

namespace gb2rpg
{

// peek x Bytes from the gbFile. Does not advance file pointer.
template<uint8_t N>
std::array<uint8_t, N> GBFile::peekBytes() 
{
    auto filePos = file.tellg();

    std::array<uint8_t, N> ret = getBytes<N>();

    // reset filepos and bytesRead
    file.seekg(filePos);
    bytesRead -= N;
    return ret;
}

// get x Bytes from the gbFile. Advances file pointer.
template<uint8_t N>
std::array<uint8_t, N> GBFile::getBytes()
{
    std::array<uint8_t, N> ret;

    file.read(reinterpret_cast<char*>(ret.data()), N);

    bytesRead += N;
    return ret;
}

}