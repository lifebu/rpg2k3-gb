#pragma once

#include <vector>
#include <string>

#include "gb2rpg/cli/CLI.h"


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
        static std::vector<lcf::EventCommand> setupMapRomHeader(int numLabels);
        static std::vector<lcf::EventCommand> setupMapRomLabel(int labelID, int numLabels, int firstVar, int secondVar);
    };
};