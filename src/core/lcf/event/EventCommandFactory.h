#pragma once

#include <string>

#include "EventCommandFactoryDef.h"

namespace lcf 
{

class EventCommand;

class EventCommandFactory 
{
public:
    static EventCommand GenNoOp();
    static void GenNoOp(EventCommand& command);

    static EventCommand GenFirstLineComment(std::string comment);
    static void GenFirstLineComment(EventCommand& command, std::string comment);

    static EventCommand GenMultiLineComment(std::string comment);
    static void GenMultiLineComment(EventCommand& command, std::string comment);

    static EventCommand GenControlVariable(ControlVariableCommand::Type type, 
        uint16_t startID, uint16_t endID, 
        ControlVariableCommand::Operation operation, 
        ControlVariableCommand::OperandTypes operandTypes, 
        int32_t firstOperand, int32_t secondOperand);
    
    static void GenControlVariable(EventCommand& command, ControlVariableCommand::Type type, 
        uint16_t startID, uint16_t endID, 
        ControlVariableCommand::Operation operation, 
        ControlVariableCommand::OperandTypes operandTypes, 
        int32_t firstOperand, int32_t secondOperand);

    static EventCommand GenLabel(uint16_t labelID);
    static void GenLabel(EventCommand& command, uint16_t labelID);

    static EventCommand GenJumpToLabel(uint16_t labelID);
    static void GenJumpToLabel(EventCommand& command, uint16_t labelID);

    static EventCommand GenConditionalBranch(ConditionalBranchCommand::Type type, 
    uint16_t LHSVariableID, 
    ConditionalBranchCommand::RHSType rhsType, uint16_t rhs, 
    ConditionalBranchCommand::Comparison comparison, bool hasElseCase);

    static void GenConditionalBranch(EventCommand& command, ConditionalBranchCommand::Type type, 
    uint16_t LHSVariableID, 
    ConditionalBranchCommand::RHSType rhsType, uint16_t rhs, 
    ConditionalBranchCommand::Comparison comparison, bool hasElseCase);

    static EventCommand GenElseBranch();
    static void GenElseBranch(EventCommand& command);

    static EventCommand GenEndBranch();
    static void GenEndBranch(EventCommand& command);

    static EventCommand GenEndEventProcessing();
    static void GenEndEventProcessing(EventCommand& command);
};

};