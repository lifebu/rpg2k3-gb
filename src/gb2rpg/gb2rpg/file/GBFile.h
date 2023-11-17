#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <cstdint>

namespace gb2rpg {
    class CLIOptions;

    // This represents a single Gameboy file usually in the .gb or .gbc format.
    class GBFile {
        struct GBHeader {
            uint8_t entryPoint[4];
            uint8_t nintendoLogo[48];
            uint8_t title[11];
            uint8_t manufacturerCode[4];
            uint8_t cgbFlag;
            uint8_t newLicenseeCode[2];
            uint8_t sgbFlag;
            uint8_t cartridgeType;
            uint8_t romSize;
            uint8_t ramSize;
            uint8_t destinationCode;
            uint8_t oldLicenseeCode;
            uint8_t versionNumber;
            uint8_t headerChecksum;
            uint8_t globalChecksum[2];
        };

    public:
        enum GBSupport {
            GAMEBOY_ONLY,
            COLOR_SUPPORT,
            COLOR_ONLY
        };

        GBFile(std::string filePath);
        GBFile(const GBFile&) = default;
        GBFile(GBFile&& other) = default;
        ~GBFile();

        // is this a valid Gameboy File?
        bool isValid();
        // read ram size from Gameboy header in KByte
        uint16_t getRamSize();
        // read rom size from Gameboy header in KByte
        uint16_t getRomSize();
        // which Gameboy revisions this rom supports.
        GBSupport getGameboySupportLevel();
        // read title from Gameboy header
        std::string getTitle();



        // peek x Bytes from the gbFile.
        template<uint8_t N>
        std::array<uint8_t, N> peekBytes();
        // get x Bytes from the gbFile. Advances file pointer.
        template<uint8_t N>
        std::array<uint8_t, N> getBytes();
        // how many Bytes are left in the file.
        int bytesRemaining();
        
        static std::vector<GBFile> genGBFiles(CLIOptions& cli);

    private:
        // read data from the Gameboy header.
        void readHeader(GBHeader& header);

        std::ifstream file;
        uint32_t bytesRead;

        GBSupport supportLevel;
        // in KByte
        uint16_t ramSize;
        // in KByte
        uint16_t romSize;
        // name of the game (read from the header)
        std::string title;

        bool valid;
    };

    // Class that can generate multiple GB files from the options provided by the command line.
    class GBFileGenerator {
    public:
        GBFileGenerator();

        std::vector<GBFile> genGBFiles(CLIOptions& cli);
        bool hadErrors();
    private:
        bool error;
    };
};

#include "GBFile.inl"