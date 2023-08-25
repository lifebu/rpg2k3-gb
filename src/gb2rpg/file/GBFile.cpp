#include "GBFile.h"

#include <iostream>
#include <cassert>

#include <core/def/MemorySizes.h>
#include <core/structure/Logger.h>

#include "gb2rpg/cli/CLI.h"


using namespace gb2rpg;

// GBFile
const static std::string ERR_FILE_NOT_FOUND = "Error, File not found: ";

// public
GBFile::GBFile(std::string path)
    : bytesRead(0), supportLevel(GAMEBOY_ONLY), valid(false)  {
    
    file.open(path, std::ios::binary);
    if (!file.is_open()) {
        core::Logger::Get()->Log(ERR_FILE_NOT_FOUND + path, core::LogLevel::ERROR);
    } else {
        valid = true;
        GBHeader header;
        file.seekg(0x100, std::ios::beg);
        file.read((char*)&header, sizeof(GBHeader));
        readHeader(header);
        file.seekg(0, std::ios::beg);
    }
}

GBFile::~GBFile() {
    file.close();
}

bool GBFile::isValid() {
    return valid;
}

uint16_t GBFile::getRamSize() {
    return ramSize;
}

uint16_t GBFile::getRomSize() {
    return romSize;
}

GBFile::GBSupport GBFile::getGameboySupportLevel() {
   return supportLevel; 
}

std::string GBFile::getTitle() {
    return title;
}

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

std::vector<GBFile> GBFile::genGBFiles(gb2rpg::CLIOptions& cli) {
    auto& filePaths = cli.getFilePaths();
    std::vector<GBFile> gbFiles;
    for(auto path : filePaths) {
        gbFiles.emplace_back(GBFile(path));
    }
    return gbFiles;
}

// private
// read data from the Gameboy header.
void GBFile::readHeader(GBHeader& header) {
    // Read ram size
    if (header.ramSize == 0x00) ramSize = 0;
    else if (header.ramSize == 0x02) ramSize = 8;
    else if (header.ramSize == 0x03) ramSize = 32;
    else if (header.ramSize == 0x04) ramSize = 128;
    else if (header.ramSize == 0x05) ramSize = 64;
    // Unknown GameBoy Header Ram Size
    else assert(false);
    
    // Read rom size
    // TODO: could probably improve this by using romSize = 32 * (header.romSize + 1);
    if (header.romSize == 0x00) romSize = 32;
    else if (header.romSize == 0x01) romSize = 64;
    else if (header.romSize == 0x02) romSize = 128;
    else if (header.romSize == 0x03) romSize = 256;
    else if (header.romSize == 0x04) romSize = 512;
    else if (header.romSize == 0x05) romSize = 1024;
    else if (header.romSize == 0x06) romSize = 2048;
    else if (header.romSize == 0x07) romSize = 4096;
    else if (header.romSize == 0x08) romSize = 8192;
    // Unknown GameBoy Header Rom Size
    else assert(false);
    
    // Read GameBoy support level
    if (header.cgbFlag == 0x00) supportLevel = GAMEBOY_ONLY;
    else if (header.cgbFlag == 0x80) supportLevel = COLOR_SUPPORT;
    else if (header.cgbFlag == 0xC0) supportLevel = COLOR_ONLY;
    // Unknown GameBoy Header Rom Size
    else assert(false);

    // Read Gameboy Title. 
    title.append((const char*)header.title);
}


// GBFileGenerator
const static std::string ERR_TO_MUCH_RAM = "Only games that need a maximum of 32kByte of Cartridge RAM are supported: ";
const static std::string ERR_NO_COLOR_SUPPORT = "Games that can run on both the Gameboy and Gameboy Color are not supported: ";
const static std::string ERR_NO_COLOR_EXCLUSIVE = "Games that exclusively run on the Gameboy Color are not supported: ";

// publlic
GBFileGenerator::GBFileGenerator() 
    : error(false)
{}

std::vector<GBFile> GBFileGenerator::genGBFiles(gb2rpg::CLIOptions& cli) {
    auto& filePaths = cli.getFilePaths();
    std::vector<GBFile> gbFiles;
    for(auto& path : filePaths) {
        GBFile file = GBFile(path);
        if (!file.isValid()) {
            error = true;
            continue;
        }

        if (file.getRamSize() > MEMORYSIZES::MAX_CARTRIDGE_RAM) {
            core::Logger::Get()->Log(ERR_TO_MUCH_RAM + path, core::LogLevel::ERROR);
            error = true;
        }

        if (file.getGameboySupportLevel() == GBFile::COLOR_SUPPORT) {
            core::Logger::Get()->Log(ERR_NO_COLOR_SUPPORT + path, core::LogLevel::ERROR);
            error = true;
        }

        if (file.getGameboySupportLevel() == GBFile::COLOR_ONLY) {
            core::Logger::Get()->Log(ERR_NO_COLOR_EXCLUSIVE + path, core::LogLevel::ERROR);
            error = true;
        }


        gbFiles.emplace_back(std::move(file));
    }
    return gbFiles;
}

bool GBFileGenerator::hadErrors() {
    return error;
}