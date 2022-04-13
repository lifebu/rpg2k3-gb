
namespace tinyxml2 {
    class XMLElement;
    class XMLDocument;
}

void DeepCloneInsertBack(tinyxml2::XMLElement* toCopy, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* insertPos);

void DeepCloneInsertBackAllSiblings(tinyxml2::XMLElement* toCopy, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* insertPos);