#include "GBFile.h"

#include "gb2rpg/pch.h"

#include <core/def/MemorySizes.h>
#include <core/structure/Logger.h>
#include <core/utilities/GBHelper.h>

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

    ramSize = ConvertRAMSizetoKByte(header.ramSize);
    romSize = ConvertROMSizetoKByte(header.romSize);
    
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
const static std::string INFO_FILE = "Using GB ROM: ";

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


        core::Logger::Get()->Log(INFO_FILE + path, core::LogLevel::INFO);
        gbFiles.emplace_back(std::move(file));
    }
    return gbFiles;
}

bool GBFileGenerator::hadErrors() {
    return error;
}