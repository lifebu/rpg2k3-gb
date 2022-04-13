
namespace tinyxml2 {
    class XMLElement;
    class XMLDocument;
}

void DeepCopyInsertBack(tinyxml2::XMLElement* toCopy, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* insertPos);

void DeepCopyInsertBackAllSiblings(tinyxml2::XMLElement* toCopy, tinyxml2::XMLDocument* doc, tinyxml2::XMLElement* insertPos);