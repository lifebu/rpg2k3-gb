#include "EventCommandFactory.h"

#include "EventCommand.h"


namespace lcf 
{

EventCommand EventCommandFactory::GenNoOp()
{
    return EventCommand(EventCommand::CommandType::NO_OP, 0, "", {});
}

void EventCommandFactory::GenNoOp(EventCommand& command)
{
    command.type = EventCommand::CommandType::NO_OP;
    //command.indentation = 0;
    command.stringParam = "";
    command.parameters.clear();
}

EventCommand EventCommandFactory::GenFirstLineComment(std::string comment)
{
    return EventCommand(EventCommand::CommandType::FIRST_LINE_COMMENT, 0, comment, {});
}

void EventCommandFactory::GenFirstLineComment(EventCommand& command, std::string comment)
{
    command.type = EventCommand::CommandType::FIRST_LINE_COMMENT;
    //command.indentation = 0;
    command.stringParam = comment;
    command.parameters.clear();
}

EventCommand EventCommandFactory::GenMultiLineComment(std::string comment)
{
    return EventCommand(EventCommand::CommandType::MULTI_LINE_COMMENT, 0, comment, {});
}

void EventCommandFactory::GenMultiLineComment(EventCommand& command, std::string comment)
{
    command.type = EventCommand::CommandType::MULTI_LINE_COMMENT;
    //command.indentation = 0;
    command.stringParam = comment;
    command.parameters.clear();
}

EventCommand EventCommandFactory::GenControlVariable(ControlVariableCommand::Type type, 
        uint16_t startID, uint16_t endID, 
        ControlVariableCommand::Operation operation, 
        ControlVariableCommand::OperandTypes operandTypes, 
        int32_t firstOperand, int32_t secondOperand)
{
    return EventCommand(EventCommand::CommandType::CONTROL_VARIABLE, 0, "", 
    {
        static_cast<int32_t>(type),
        static_cast<int32_t>(startID),
        static_cast<int32_t>(endID),
        static_cast<int32_t>(operandTypes),
        firstOperand,
        secondOperand
    });
}

void EventCommandFactory::GenControlVariable(EventCommand& command,      
        ControlVariableCommand::Type type, 
        uint16_t startID, uint16_t endID, 
        ControlVariableCommand::Operation operation, 
        ControlVariableCommand::OperandTypes operandTypes, 
        int32_t firstOperand, int32_t secondOperand)
{
    command.type = EventCommand::CommandType::CONTROL_VARIABLE;
    //command.indentation = 0;
    command.stringParam = "";
    command.parameters.clear();
    command.parameters.insert(command.parameters.end(),
    {
        static_cast<int32_t>(type),
        static_cast<int32_t>(startID),
        static_cast<int32_t>(endID),
        static_cast<int32_t>(operandTypes),
        firstOperand,
        secondOperand
    });
}

EventCommand EventCommandFactory::GenLabel(uint16_t labelID)
{
    return EventCommand(EventCommand::CommandType::LABEL, 0, "", 
    {
        static_cast<int32_t>(labelID)
    });
}

void EventCommandFactory::GenLabel(EventCommand& command, uint16_t labelID)
{
    command.type = EventCommand::CommandType::LABEL;
    //command.indentation = 0;
    command.stringParam = "";
    command.parameters.clear();
    command.parameters.insert(command.parameters.end(),
    {
        static_cast<int32_t>(labelID)
    });
}

EventCommand EventCommandFactory::GenJumpToLabel(uint16_t labelID)
{
    return EventCommand(EventCommand::CommandType::JUMP_TO_LABEL, 0, "", 
    {
        static_cast<int32_t>(labelID)
    });
}

void EventCommandFactory::GenJumpToLabel(EventCommand& command, uint16_t labelID)
{
    command.type = EventCommand::CommandType::JUMP_TO_LABEL;
    command.indentation = 0;
    command.stringParam = "";
    command.parameters.clear();
    command.parameters.insert(command.parameters.end(),
    {
        static_cast<int32_t>(labelID)
    });
}

EventCommand EventCommandFactory::GenConditionalBranch(ConditionalBranchCommand::Type type, 
    uint16_t LHSVariableID, 
    ConditionalBranchCommand::RHSType rhsType, uint16_t rhs, 
    ConditionalBranchCommand::Comparison comparison, bool hasElseCase)
{
    // TYPE VARID ISCONST RHS COMPARE ELSE
    return EventCommand(EventCommand::CommandType::CONDITIONAL_BRANCH, 0, "", 
    {
        static_cast<int32_t>(type),
        static_cast<int32_t>(LHSVariableID),
        static_cast<int32_t>(rhsType),
        static_cast<int32_t>(rhs),
        static_cast<int32_t>(comparison),
        static_cast<int32_t>(hasElseCase ? 1 : 0)
    });
}

void EventCommandFactory::GenConditionalBranch(EventCommand& command,
    ConditionalBranchCommand::Type type, 
    uint16_t LHSVariableID, 
    ConditionalBranchCommand::RHSType rhsType, uint16_t rhs, 
    ConditionalBranchCommand::Comparison comparison, bool hasElseCase)
{
    command.type = EventCommand::CommandType::CONDITIONAL_BRANCH;
    //command.indentation = 0;
    command.stringParam = "";
    command.parameters.clear();
    command.parameters.insert(command.parameters.end(),
    {
        static_cast<int32_t>(type),
        static_cast<int32_t>(LHSVariableID),
        static_cast<int32_t>(rhsType),
        static_cast<int32_t>(rhs),
        static_cast<int32_t>(comparison),
        static_cast<int32_t>(hasElseCase ? 1 : 0)
    });
}


EventCommand EventCommandFactory::GenElseBranch()
{
    return EventCommand(EventCommand::CommandType::ELSE_BRANCH, 0, "", {});
}

void EventCommandFactory::GenElseBranch(EventCommand& command)
{
    command.type = EventCommand::CommandType::ELSE_BRANCH;
    //command.indentation = 0;
    command.stringParam = "";
    command.parameters.clear();
}

EventCommand EventCommandFactory::GenEndBranch()
{
    return EventCommand(EventCommand::CommandType::END_BRANCH, 0, "", {});
}

void EventCommandFactory::GenEndBranch(EventCommand& command)
{
    command.type = EventCommand::CommandType::END_BRANCH;
    //command.indentation = 0;
    command.stringParam = "";
    command.parameters.clear();
}

EventCommand EventCommandFactory::GenEndEventProcessing()
{
    return EventCommand(EventCommand::CommandType::END_EVENT_PROCESSING, 0, "", {});
}

void EventCommandFactory::GenEndEventProcessing(EventCommand& command)
{
    command.type = EventCommand::CommandType::END_EVENT_PROCESSING;
    //command.indentation = 0;
    command.stringParam = "";
    command.parameters.clear();
}

};