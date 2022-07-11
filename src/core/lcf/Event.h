#pragma once

#include<string>

namespace tinyxml2 {
    class XMLDocument;
};


void setEventIDNameCoord(tinyxml2::XMLDocument* event, int id, std::string& name, int x, int y);
void setEventPageID(tinyxml2::XMLDocument* eventPage, int id);