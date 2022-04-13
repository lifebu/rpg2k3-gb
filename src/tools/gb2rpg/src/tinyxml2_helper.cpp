#include"tinyxml2_helper.h"

#include "thirdparty/tinyxml2/tinyxml2.h"

/*
* if insertPos is nullptr, it will insert the copy as a new child to document.
*/
void DeepCopyInsertBack(tinyxml2::XMLElement* toCopy, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* insertPos) {
    auto* copy = toCopy->DeepClone(doc);
    if(insertPos) insertPos->InsertEndChild(copy);
    else doc->InsertEndChild(copy);
}

void DeepCopyInsertBackAllSiblings(tinyxml2::XMLElement* toCopy, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* insertPos) {
    while (toCopy) {
        DeepCopyInsertBack(toCopy, doc, insertPos);
        toCopy = toCopy->NextSiblingElement();
    }
}