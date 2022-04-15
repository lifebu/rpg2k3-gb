#include <vector>
#include <fstream>
#include <string>

class CLIOptions;

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
    GBFile(std::string filePath);
    GBFile(const GBFile&) = default;
    GBFile(GBFile&& other) = default;
    ~GBFile();

    // read ram size from Gameboy header in KByte
    uint16_t getRamSize();
    // read rom size from Gameboy header in KByte
    uint16_t getRomSize();

    // peek x Bytes from the gbFile.
    std::vector<uint8_t> peekBytes(int numBytes);
    // get x Bytes from the gbFile. Advances file pointer.
    std::vector<uint8_t> getBytes(int numBytes);
    // how many Bytes are left in the file.
    int bytesRemaining();
    
    static std::vector<GBFile> genGBFiles(CLIOptions& cli);

private:
    // read ram size from Gameboy header in KByte
    uint16_t readRamSize(GBHeader& header);
    // read rom size from Gameboy header in KByte
    uint16_t readRomSize(GBHeader& header);

    std::ifstream file;
    uint32_t bytesRead;
    // in KByte
    uint16_t ramSize;
    // in KByte
    uint16_t romSize;
};