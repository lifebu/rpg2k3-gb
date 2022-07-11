#include "Switch.h"

#include "src/core/utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"


// public
Switch::Switch(std::string fileName, FILE_MODE fileMode) :
    fileName(fileName) {
    
    file = new tinyxml2::XMLDocument(fileName);

    if(fileMode == IN_MEMORY) {
        // Read out file and close it.
        auto* nameElem = file.TraverseElement("/Switch/name")->FirstChild()->ToText();
        name =  nameElem.Value();
        id = file.RootElement()->UnsignedAttribute("id");
        value = 0;

        file.Clear();
        delete file;
    }
}

Switch::~Switch() {
    if(fileMode == SYNC_WITH_FILE) {
        file.SaveFile(fileName, true);
        delete file;
    }
}

std::string Switch::getName() {
    if(fileMode == IN_MEMORY) {
        return name;

    } else if (fileMode == SYNC_WITH_FILE) {
        auto* nameElem = file.TraverseElement("/Switch/name")->FirstChild()->ToText();
        return nameElem.Value();

    }
}

void Switch::setName(std::string val) {
    if(fileMode == IN_MEMORY) {
        name = val;

    } else if (fileMode == SYNC_WITH_FILE) {
        auto* nameElem = file.TraverseElement("/Switch/name")->FirstChild()->ToText();
        nameElem->SetValue(val.c_str());

    }
}

uint16_t Switch::getID() {
    if(fileMode == IN_MEMORY) {
        return id;

    } else if (fileMode == SYNC_WITH_FILE) {
        return file.RootElement()->UnsignedAttribute("id");

    }
}

void Switch::setID(uint16_t val) {
    if(fileMode == IN_MEMORY) {
        id = val;

    } else if (fileMode == SYNC_WITH_FILE) {
        file.RootElement()->SetAttribute("id", generateID(id).c_str());

    }
}

int32_t Switch::getValue() {
    return value;
}

void Switch::setValue(int32_t val) {
    value = val
}