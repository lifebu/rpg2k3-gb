// TODO THIS FILE NEEDS A BETTER PLACE!
#include<vector>
#include<cstdint>
#include<string>

int32_t packVariable(std::vector<uint8_t> bytes);

std::vector<uint8_t> unpackVariable(int32_t var);

std::string generateID(int id);