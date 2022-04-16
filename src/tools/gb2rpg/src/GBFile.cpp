#include "GBFile.h"

#include "CLI.h"

#include <iostream>
#include <cassert>

using namespace std;

// public
GBFile::GBFile(string path)
    : bytesRead(0)  {
    
    file.open(path, ios::binary);
    if (!file.is_open()) {
        std::cout << "Error, File not found: " << path << "\n"; 
    } else {
        file.seekg(0x100, std::ios::beg);
        GBHeader header;
        file.read((char*)&header, sizeof(GBHeader));
        ramSize = readRamSize(header);
        romSize = readRomSize(header);

        file.seekg(0, std::ios::beg);
    }
}
GBFile::~GBFile() {
    file.close();
}



uint16_t GBFile::getRamSize() {
    return ramSize;
};
uint16_t GBFile::getRomSize() {
    return romSize;
};

// peek x Bytes from the gbFile. Does not advance file pointer.
std::vector<uint8_t> GBFile::peekBytes(int numBytes) {
    auto filePos = file.tellg();

    std::vector<uint8_t> ret = getBytes(numBytes);

    // reset filepos and bytesRead
    file.seekg(filePos);
    bytesRead -= numBytes;
    return ret;
}

// get x Bytes from the gbFile. Advances file pointer.
std::vector<uint8_t> GBFile::getBytes(int numBytes) {
    std::vector<uint8_t> ret;
    ret.reserve(numBytes);

    char val[numBytes] = {};
    // If numBytes > remainingBytes => The last bytes in the array will be untouched => equal to zero.
    file.read(val, numBytes);
    ret.insert(ret.end(), val, val + numBytes);

    bytesRead += numBytes;
    return ret;
}

// how many Bytes are left in the file.
int GBFile::bytesRemaining() {
    // .gb files have the same size as the original rom.
    int fileSize = romSize * 1024;
    return fileSize - bytesRead;
}

std::vector<GBFile> GBFile::genGBFiles(CLIOptions& cli) {
    auto& filePaths = cli.getFilePaths();
    std::vector<GBFile> gbFiles;
    for(auto path : filePaths) {
        gbFiles.emplace_back(GBFile(path));
    }
    return gbFiles;
}

// private
// read ram size from Gameboy header in KByte
uint16_t GBFile::readRamSize(GBHeader& header) {
    if (header.ramSize == 0x00) return 0;
    if (header.ramSize == 0x02) return 8;
    if (header.ramSize == 0x03) return 32;
    if (header.ramSize == 0x04) return 128;
    if (header.ramSize == 0x05) return 64;
    // Unknown GameBoy Header Ram Size
    assert(false);
    return 0;
}
// read rom size from Gameboy header in KByte
uint16_t GBFile::readRomSize(GBHeader& header) {
    if (header.romSize == 0x00) return 32;
    if (header.romSize == 0x01) return 64;
    if (header.romSize == 0x02) return 128;
    if (header.romSize == 0x03) return 256;
    if (header.romSize == 0x04) return 512;
    if (header.romSize == 0x05) return 1024;
    if (header.romSize == 0x06) return 2048;
    if (header.romSize == 0x07) return 4096;
    if (header.romSize == 0x08) return 8192;
    // Unknown GameBoy Header Rom Size
    assert(false);
    return 0;
}