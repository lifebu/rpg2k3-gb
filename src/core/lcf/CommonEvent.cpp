#include "CommonEvent.h"

#include "src/core/utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"


// public
CommonEvent::CommonEvent(std::string fileName, FILE_MODE fileMode) :
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

CommonEvent::~CommonEvent() {
    if(fileMode == SYNC_WITH_FILE) {
        file.SaveFile(fileName, true);
        delete file;
    }
}

std::string CommonEvent::getName();
void CommonEvent::setName(std::string val);

bool CommonEvent::getUseConditionSwitch();
void CommonEvent::setUseConditionSwitch(bool val);

uint16_t CommonEvent::getConditionSwitchID() {
    
}

void CommonEvent::setConditionSwitchID(uint16_t val) {

}

void CommonEvent::addEventCommand(EventCommand& eventCommand) {

}