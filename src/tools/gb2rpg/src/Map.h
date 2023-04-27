#pragma once

#include "CLI.h"

#include <vector>
#include <string>


namespace lcf {
    class Map;
    class EventCommand;
};

namespace gb2rpg {
    class GBFile;

    class Map {
    public:
        Map() = delete;

        static void genMapFiles(std::vector<GBFile>& gbFiles, CLIOptions::XMLParser parserToUse);

    private:
        static void generateDMGROM(lcf::Map& map);
        static void generateMapROM(lcf::Map& map, GBFile& gbFile, int numOfMapROMs);
        static void generateMapRAM(lcf::Map& map);

        // Helper functions
        static int calcNumOfLabels(GBFile& gbFile);
        static bool isLastEventPage(GBFile& gbFile);
        static void setupMapRomHeader(std::vector<lcf::EventCommand>& mapRomHeader, int numLabels);
        static void setupMapRomLabel(std::vector<lcf::EventCommand>& mapRomLabel, int labelID, int numLabels, int firstVar, int secondVar);
    };
};