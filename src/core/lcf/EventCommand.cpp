#include "EventCommand.h"

#include "src/core/utilities/RPGHelper.h"
#include "thirdparty/tinyxml2/tinyxml2.h"


namespace lcf {

// public
EventCommand::EventCommand(CommandType type, uint8_t indentation, std::string stringParam, std::vector<int32_t> parameters) :
    type(type), indentation(indentation), stringParam(stringParam), parameters(parameters) {
    // TODO: use getters/setters for checks?
}

};