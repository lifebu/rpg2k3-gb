#pragma once

#include "../lcf/database/CommonEvent.h"

#include <string>
#include <memory>

namespace tinyxml2 {class XMLDocument; class XMLElement;};


namespace lcf {

class CommonEventSerializer
{
    friend class DatabaseSerializer;

public:
    static std::vector<CommonEvent> MultipleFromFile(std::string fileName);
    static void MultipleToFile(std::string fileName, std::vector<CommonEvent>& elems);

private:
    static CommonEvent FromFileImpl(tinyxml2::XMLElement* commonEvent);
    static void ToFileImpl(const CommonEvent& elem, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* commonEvent);
};

};