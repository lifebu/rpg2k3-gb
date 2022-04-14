#include"tinyxml2_helper.h"

#include "thirdparty/tinyxml2/tinyxml2.h"

#include <cassert>

using namespace std;

/*
* if insertPos is nullptr, it will insert the copy as a new child to document.
*/
void DeepCloneInsertBack(tinyxml2::XMLNode* toCopy, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* insertPos) {
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

string generateID(int id) {
    assert(id > 0 && id < 10000);
    string str;
    // Add leading zeroes.
    if (id < 1000) str += "0";
    if (id < 100) str += "0";
    if (id < 10) str += "0";

    str += to_string(id);

    return str;
}