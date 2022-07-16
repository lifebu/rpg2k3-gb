#pragma once

#include "Filemode.h"

#include <string>
#include <vector>

namespace tinyxml2 { class XMLDocument; }
class Event;


class Map {
public:
    Map(std::string fileName, FILE_MODE fileMode);
    Map(const Map& other) = delete;
    Map(Map&& other) = delete;
    ~Map();
    
    Map& operator=(const Map& other) = delete;
    Map& operator=(Map&& other) = delete;

private:
    tinyxml2::XMLDocument* file;
    std::string fileName;

    std::vector<Event> events;
};