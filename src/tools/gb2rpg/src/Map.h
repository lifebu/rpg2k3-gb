#pragma once

#include <vector>
#include <string>

class GBFile;
namespace tinyxml2 {
    class XMLDocument;
};

class Map {
public:
    Map(GBFile& gbFile);
    ~Map();


    // TODO: 
    // could make this non-copyable but moveable, makes semantic sense.
    //  - could save gbFile to recreate event on copy 
    //  - shallow copy on event => BUT this requires other to be non-const. 
    Map(const Map& other) {
        throw;
    };
    Map& operator=(const Map& other) = delete;

    Map(Map&& other) {
        throw;
    };
    Map& operator=(Map&& other) = delete;

    static void genMapFiles(std::vector<GBFile>& gbFiles);

private:
    void generateDMGROM();
    void generateMapROM(GBFile& gbFile, int numOfMapROMs);
    void generateMapRAM();

    // Helper functions
    int calcNumOfLabels(GBFile& gbFile);
    bool isLastEventPage(GBFile& gbFile);
    void setupMapRomHeader(tinyxml2::XMLDocument* mapRomHeader, int numLabels);
    void setupMapRomLabel(tinyxml2::XMLDocument* mapRomLabel, int labelID, int numLabels, int firstVar, int secondVar);

    // TODO: Temporary:
    void setEventIDNameCoord(tinyxml2::XMLDocument* event, int id, std::string& name, int x, int y);

    tinyxml2::XMLDocument* mapDoc;
    // MAP RAM Events start with this ID.
    int mapRAMID;
};