#include "EventCommand.h"

#include "src/core/utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"


// public
EventCommand::EventCommand(std::string fileName, FILE_MODE fileMode) :
    fileName(fileName) {
    
    file = new tinyxml2::XMLDocument(fileName);

    if(fileMode == IN_MEMORY) {
        // Read out file and close it.

        file.Clear();
        delete file;
    }
}

EventCommand::~EventCommand() {
    if(fileMode == SYNC_WITH_FILE) {
        file.SaveFile(fileName, true);
        delete file;
    }
}