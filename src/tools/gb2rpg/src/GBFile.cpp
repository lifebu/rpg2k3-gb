#include "GBFile.h"

#include <iostream>

using namespace std;


GBFile::GBFile(string path) {
    file.open(path, ios::binary);
    if (!file.is_open()) {
        std::cout << "Error, File not found: " << path << "\n"; 
    } else {
        file.seekg(0x100, std::ios::beg);
        file.read((char*)&header, sizeof(GBHeader));
    }
}


uint16_t GBFile::getRamSize() {
    if (header.ramSize == 0x00) return 0;
    if (header.ramSize == 0x02) return 8;
    if (header.ramSize == 0x03) return 32;
    if (header.ramSize == 0x04) return 128;
    if (header.ramSize == 0x05) return 64;
    static_assert(true, "Unknown GameBoy Header Ram Size");
    return 0;
};

// read rom size from Gameboy header in KByte
uint16_t GBFile::getRomSize() {
    if (header.romSize == 0x00) return 32;
    if (header.romSize == 0x01) return 64;
    if (header.romSize == 0x02) return 128;
    if (header.romSize == 0x03) return 256;
    if (header.romSize == 0x04) return 512;
    if (header.romSize == 0x05) return 1024;
    if (header.romSize == 0x06) return 2048;
    if (header.romSize == 0x07) return 4096;
    if (header.romSize == 0x08) return 8192;
    static_assert(true, "Unknown GameBoy Header Rom Size");
    return 0;
};

std::vector<GBFile> GBFile::genGBFiles(CLIOptions& cli) {
    
}