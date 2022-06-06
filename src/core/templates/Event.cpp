#include "Event.h"

#include "thirdparty/tinyxml2/tinyxml2.h"

#include <cassert>


void setEventIDNameCoord(tinyxml2::XMLDocument* event, int id, std::string& name, int x, int y) {
    assert(x >= 0 && x < RPGMAKER::MAP_SIZE_X);
    assert(y >= 0 && y < RPGMAKER::MAP_SIZE_Y);

    // Set Event ID
    event->RootElement()->SetAttribute("id", generateID(id).c_str());

    // Set Event Name
    auto* nameElem = event->TraverseElement("//name")->FirstChild();
    nameElem->SetValue((name).c_str());

    // Set Event Coordinates
    auto* xCoord = event->TraverseElement("//x")->FirstChild();
    xCoord->SetValue(to_string((id - 1) % RPGMAKER::MAP_SIZE_X).c_str());

    auto* yCoord = event->TraverseElement("//y")->FirstChild();
    yCoord->SetValue(to_string((id - 1) / RPGMAKER::MAP_SIZE_Y).c_str());
}
void setEventPageID(tinyxml2::XMLDocument* eventPage, int id) {

}