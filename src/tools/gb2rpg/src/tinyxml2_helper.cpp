#include"tinyxml2_helper.h"

#include "thirdparty/tinyxml2/tinyxml2.h"

#include <cassert>

using namespace std;

/*
* if insertPos is nullptr, it will insert the copy as a new child to document.
*/
void DeepCloneInsertBack(tinyxml2::XMLNode* toCopy, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* insertPos) {
    //TODO: calling DeepClone/ShallowClone creates a leak somehow (?)
    /*
    // Total: 180kB
    int a = 10;
    {
        tinyxml2::XMLDocument map;
        map.LoadFile(TEMPLATES::MAP);
        tinyxml2::XMLDocument t;

        // Total 2.716kB

        // Creates 2.656, New Total: 5.372kB
        auto* copy = map.RootElement()->DeepClone(&t);
    }
    // Total: 240kB, 60kByte Leaked: 
    int b = 10;
    */
    auto* copy = toCopy->DeepClone(doc);
    if(insertPos) insertPos->InsertEndChild(copy);
    else doc->InsertEndChild(copy);
}

void DeepCloneInsertBackAllSiblings(tinyxml2::XMLNode* toCopy, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* insertPos) {
    while (toCopy) {
        DeepCloneInsertBack(toCopy, doc, insertPos);
        toCopy = toCopy->NextSiblingElement();
    }
}