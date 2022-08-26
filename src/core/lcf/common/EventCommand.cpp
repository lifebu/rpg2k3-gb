#include "EventCommand.h"

#include "utilities/RPGHelper.h"


namespace lcf {

// public
EventCommand::EventCommand(
    const CommandType type, const uint8_t indentation, 
    const std::string stringParam, 
    const std::vector<int32_t> parameters) :
    type(type), indentation(indentation), stringParam(stringParam), parameters(parameters) {
}


};