#include "Variable.h"

#include "src/core/utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"


// public
Variable::Variable(std::string fileName, FILE_MODE fileMode) :
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

Variable::~Variable() {
    if(fileMode == SYNC_WITH_FILE) {
        file.SaveFile(fileName, true);
        delete file;
    }
}

std::string Variable::getName() {
    if(fileMode == IN_MEMORY) {
        return name;

    } else if (fileMode == SYNC_WITH_FILE) {
        auto* nameElem = file.TraverseElement("/Switch/name")->FirstChild()->ToText();
        return nameElem.Value();

    }
}

void Variable::setName(std::string val) {
    if(fileMode == IN_MEMORY) {
        name = val;

    } else if (fileMode == SYNC_WITH_FILE) {
        auto* nameElem = file.TraverseElement("/Switch/name")->FirstChild()->ToText();
        nameElem->SetValue(val.c_str());

    }
}

uint16_t Variable::getID() {
    if(fileMode == IN_MEMORY) {
        return id;

    } else if (fileMode == SYNC_WITH_FILE) {
        return file.RootElement()->UnsignedAttribute("id");

    }
}

void Variable::setID(uint16_t val) {
    if(fileMode == IN_MEMORY) {
        id = val;

    } else if (fileMode == SYNC_WITH_FILE) {
        file.RootElement()->SetAttribute("id", generateID(id).c_str());

    }
}

bool Variable::getValue() {
    return value;
}

void Variable::setValue(bool val) {
    value = val
}