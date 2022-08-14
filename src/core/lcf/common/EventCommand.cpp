#include "EventCommand.h"

#include "utilities/RPGHelper.h"


namespace lcf {

// public
EventCommand::EventCommand(CommandType type, uint8_t indentation, std::string stringParam, std::vector<int32_t> parameters) :
    type(type), indentation(indentation), stringParam(stringParam), parameters(parameters) {
    // TODO: use getters/setters for checks?
}

void EventCommand::setParameters(std::vector<int32_t> parameters) {
    this->parameters = parameters;
}

void EventCommand::setType(CommandType type) {
    this->type = type;
}

};