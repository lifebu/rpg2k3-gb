#include <string>
#include <fstream>
#include <cassert>
#include <iostream>


typedef uint8_t byte;

// structure of the Gameboy header @ 0x0100
struct GBHeader {
    byte entryPoint[4];
    byte nintendoLogo[48];
    uint8_t title[11];
    uint8_t manufacturerCode[4];
    byte cgbFlag;
    byte newLicenseeCode[2];
    byte sgbFlag;
    byte cartridgeType;
    byte romSize;
    byte ramSize;
    byte destinationCode;
    byte oldLicenseeCode;
    byte versionNumber;
    byte headerChecksum;
    byte globalChecksum[2];
};

// read ram size from Gameboy header in KByte
uint16_t readRamSize(GBHeader gbHeader) {
    if (gbHeader.ramSize == 0x00) return 0;
    if (gbHeader.ramSize == 0x02) return 8;
    if (gbHeader.ramSize == 0x03) return 32;
    if (gbHeader.ramSize == 0x04) return 128;
    if (gbHeader.ramSize == 0x05) return 64;
    static_assert(true, "Unknown GameBoy Header Ram Size");
    return 0;
};

// read rom size from Gameboy header in KByte
uint16_t readRomSize(GBHeader gbHeader) {
    if (gbHeader.romSize == 0x00) return 32;
    if (gbHeader.romSize == 0x01) return 64;
    if (gbHeader.romSize == 0x02) return 128;
    if (gbHeader.romSize == 0x03) return 256;
    if (gbHeader.romSize == 0x04) return 512;
    if (gbHeader.romSize == 0x05) return 1024;
    if (gbHeader.romSize == 0x06) return 2048;
    if (gbHeader.romSize == 0x07) return 4096;
    if (gbHeader.romSize == 0x08) return 8192;
    static_assert(true, "Unknown GameBoy Header Rom Size");
    return 0;
};


int main (int argc, char* argv[]) {
    // parameters
    std::string filePath = "Tetris.gb";

    std::begin(filePath);

    // read the cl-arguments
    for (int i = 0; i < argc; ++i) {
        if (argv[i] == "-f" && i + 1 <= argc) {
            filePath = argv[i + 1];
        }
    }

    // open gb file
    std::ifstream gbFile;
    gbFile.open(filePath, std::ios::binary);
    if (!gbFile.is_open()) {
        std::cout << "Error, File not found: " << filePath << "\n"; 
        return 0;
    }

    // read Gameboy header
    GBHeader gbHeader;
    gbFile.seekg(0x100, std::ios::beg);
    gbFile.read((char*)&gbHeader, sizeof(GBHeader));

    // read ram- and romsize
    uint16_t ramSize = readRamSize(gbHeader);
    if (ramSize > 32) std::cout << "Error: Emulator does not support cartridges with more than 32KByte of RAM, this cartridge needs " << ramSize << "KByte." << "\n";
    uint16_t romSize = readRomSize(gbHeader);

    std::cout << "ram size: " << ramSize << "kB, rom size: " << romSize << "kB\n";

    return 0;
}