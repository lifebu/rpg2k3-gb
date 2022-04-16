#include<string>

namespace tinyxml2 {
    class XMLElement;
    class XMLDocument;
    class XMLNode;
}

void DeepCloneInsertBack(tinyxml2::XMLNode* toCopy, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* insertPos);

void DeepCloneInsertBackAllSiblings(tinyxml2::XMLNode* toCopy, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* insertPos);