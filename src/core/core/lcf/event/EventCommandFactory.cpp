#include "EventCommandFactory.h"

#include "core/lcf/event/EventCommand.h"
#include "core/structure/Logger.h"


namespace lcf 
{

// NoOp
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

// Comments and Textboxes
EventCommand EventCommandFactory::GenFirstLineShowText(std::string text)
{
    return EventCommand(EventCommand::CommandType::FIRST_LINE_SHOW_TEXT, 0, text, {});
}

void EventCommandFactory::GenFirstLineShowText(EventCommand& command, std::string text)
{
    command.type = EventCommand::CommandType::FIRST_LINE_SHOW_TEXT;
    //command.indentation = 0;
    command.stringParam = text;
    command.parameters.clear();
}

EventCommand EventCommandFactory::GenMultiLineShowText(std::string text)
{
    return EventCommand(EventCommand::CommandType::MULTI_LINE_SHOW_TEXT, 0, text, {});
}

void EventCommandFactory::GenMultiLineShowText(EventCommand& command, std::string text)
{
    command.type = EventCommand::CommandType::MULTI_LINE_SHOW_TEXT;
    //command.indentation = 0;
    command.stringParam = text;
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


// Control Variables
EventCommand EventCommandFactory::GenControlVariable(ControlVariable::Type type, 
        uint16_t startID, uint16_t endID, 
        ControlVariable::Operation operation, 
        ControlVariable::OperandTypes operandTypes, 
        int32_t firstOperand, int32_t secondOperand)
{
    return EventCommand(EventCommand::CommandType::CONTROL_VARIABLE, 0, "", 
    {
        static_cast<int32_t>(type),
        static_cast<int32_t>(startID),
        static_cast<int32_t>(endID),
        static_cast<int32_t>(operation),
        static_cast<int32_t>(operandTypes),
        firstOperand,
        secondOperand
    });
}

void EventCommandFactory::GenControlVariable(EventCommand& command,      
        ControlVariable::Type type, 
        uint16_t startID, uint16_t endID, 
        ControlVariable::Operation operation, 
        ControlVariable::OperandTypes operandTypes, 
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
        static_cast<int32_t>(operation),
        static_cast<int32_t>(operandTypes),
        firstOperand,
        secondOperand
    });
}

EventCommand EventCommandFactory::GenChoices(std::vector<std::string> choices, bool includeCancel)
{
    return EventCommand(EventCommand::CommandType::CHOICES, 0, GenChoicesString(choices), 
    {
        static_cast<int32_t>(GenChoiceID(choices, includeCancel))
    });
}

// Show Choices
void EventCommandFactory::GenChoices(EventCommand& command, std::vector<std::string> choices, bool includeCancel)
{
    command.type = EventCommand::CommandType::CHOICES;
    //command.indentation = 0;
    command.stringParam = GenChoicesString(choices);
    command.parameters.clear();
    command.parameters.insert(command.parameters.end(),
    {
        static_cast<int32_t>(GenChoiceID(choices, includeCancel))
    });
}

EventCommand EventCommandFactory::GenChoiceCase(std::string choiceName, Choices::ChoiceCaseOnCancel cancelBehaviour)
{
    return EventCommand(EventCommand::CommandType::CHOICE_CASE, 0, choiceName, 
    {
        static_cast<int32_t>(cancelBehaviour)
    });
}

void EventCommandFactory::GenChoiceCase(EventCommand& command, std::string choiceName, Choices::ChoiceCaseOnCancel cancelBehaviour)
{
    command.type = EventCommand::CommandType::CHOICE_CASE;
    //command.indentation = 0;
    command.stringParam = choiceName;
    command.parameters.clear();
    command.parameters.insert(command.parameters.end(),
    {
        static_cast<int32_t>(cancelBehaviour)
    });
}

EventCommand EventCommandFactory::GenChoiceBranchEnd()
{
    return EventCommand(EventCommand::CommandType::CHOICE_BRANCH_END, 0, "", {});
}

void EventCommandFactory::GenChoiceBranchEnd(EventCommand& command)
{
    command.type = EventCommand::CommandType::CHOICE_BRANCH_END;
    //command.indentation = 0;
    command.stringParam = "";
    command.parameters.clear();
}

// Input Number
EventCommand EventCommandFactory::GetInputNumber(int32_t numberOfDigits, uint16_t storageVarID)
{
    return EventCommand(EventCommand::CommandType::INPUT_NUMBER, 0, "", 
    {
        numberOfDigits,
        static_cast<int32_t>(storageVarID)
    });
}

void EventCommandFactory::GetInputNumber(EventCommand& command, int32_t numberOfDigits, uint16_t storageVarID)
{
    command.type = EventCommand::CommandType::INPUT_NUMBER;
    //command.indentation = 0;
    command.stringParam = "";
    command.parameters.clear();
    command.parameters.insert(command.parameters.end(),
    {
        numberOfDigits,
        static_cast<int32_t>(storageVarID)
    });
}

// Label
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

// Conditional Branch
EventCommand EventCommandFactory::GenConditionalBranch(ConditionalBranch::Type type, 
    uint16_t LHSVariableID, 
    ConditionalBranch::RHSType rhsType, uint16_t rhs, 
    ConditionalBranch::Comparison comparison, bool hasElseCase)
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
    ConditionalBranch::Type type, 
    uint16_t LHSVariableID, 
    ConditionalBranch::RHSType rhsType, uint16_t rhs, 
    ConditionalBranch::Comparison comparison, bool hasElseCase)
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


// Events
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

// Helper
std::string EventCommandFactory::GenChoicesString(std::vector<std::string>& choices)
{
    std::string ret;

    for(auto& choice : choices)
    {
        ret += choice;
        if(ret != *(choices.end() - 1))
        {
            ret += ", ";
        }
    }

    return ret;
}

int EventCommandFactory::GenChoiceID(std::vector<std::string>& choices, bool includeCancel)
{
    if(choices.size() > 4)
    {
        core::Logger::Get()->Log("More than 4 choices are not supported!", core::LogLevel::WARNING);
        return 0;
    }

    int choiceID = choices.size();
    if(choices.size() == 4 && includeCancel)
    {
        choiceID++;
    }

    return choiceID;
}

};