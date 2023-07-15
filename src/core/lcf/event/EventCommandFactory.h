#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "EventCommandFactoryDef.h"

namespace lcf 
{

class EventCommand;

class EventCommandFactory 
{
public:
    // TODO: Change Item, Change Party Member, Change EXP, change parameters, change equipment, set event location, get event id, erase event, call event, show picture, show/hide player, key input processing

    // NoOp
    static EventCommand GenNoOp();
    static void GenNoOp(EventCommand& command);

    // Comments and Textboxes
    static EventCommand GenFirstLineShowText(std::string text);
    static void GenFirstLineShowText(EventCommand& command, std::string text);

    static EventCommand GenMultiLineShowText(std::string text);
    static void GenMultiLineShowText(EventCommand& command, std::string text);

    static EventCommand GenFirstLineComment(std::string comment);
    static void GenFirstLineComment(EventCommand& command, std::string comment);

    static EventCommand GenMultiLineComment(std::string comment);
    static void GenMultiLineComment(EventCommand& command, std::string comment);

    // Control Variables
    static EventCommand GenControlVariable(ControlVariable::Type type, 
        uint16_t startID, uint16_t endID, 
        ControlVariable::Operation operation, 
        ControlVariable::OperandTypes operandTypes, 
        int32_t firstOperand, int32_t secondOperand);
    
    static void GenControlVariable(EventCommand& command, ControlVariable::Type type, 
        uint16_t startID, uint16_t endID, 
        ControlVariable::Operation operation, 
        ControlVariable::OperandTypes operandTypes, 
        int32_t firstOperand, int32_t secondOperand);

    // Show Choices
    static EventCommand GenChoices(std::vector<std::string> choices, bool includeCancel);
    static void GenChoices(EventCommand& command, std::vector<std::string> choices, bool includeCancel); 

    static EventCommand GenChoiceCase(std::string choiceName, Choices::ChoiceCaseOnCancel cancelBehaviour);
    static void GenChoiceCase(EventCommand& command, std::string choiceName, Choices::ChoiceCaseOnCancel cancelBehaviour); 

    static EventCommand GenChoiceBranchEnd();
    static void GenChoiceBranchEnd(EventCommand& command); 

    // Input Number
    static EventCommand GetInputNumber(int32_t numberOfDigits, uint16_t storageVarID);
    static void GetInputNumber(EventCommand& command, int32_t numberOfDigits, uint16_t storageVarID); 

    // Label
    static EventCommand GenLabel(uint16_t labelID);
    static void GenLabel(EventCommand& command, uint16_t labelID);

    static EventCommand GenJumpToLabel(uint16_t labelID);
    static void GenJumpToLabel(EventCommand& command, uint16_t labelID);

    // Conditional Branch
    static EventCommand GenConditionalBranch(ConditionalBranch::Type type, 
    uint16_t LHSVariableID, 
    ConditionalBranch::RHSType rhsType, uint16_t rhs, 
    ConditionalBranch::Comparison comparison, bool hasElseCase);

    static void GenConditionalBranch(EventCommand& command, ConditionalBranch::Type type, 
    uint16_t LHSVariableID, 
    ConditionalBranch::RHSType rhsType, uint16_t rhs, 
    ConditionalBranch::Comparison comparison, bool hasElseCase);

    static EventCommand GenElseBranch();
    static void GenElseBranch(EventCommand& command);

    static EventCommand GenEndBranch();
    static void GenEndBranch(EventCommand& command);

    // Events
    static EventCommand GenEndEventProcessing();
    static void GenEndEventProcessing(EventCommand& command);

private:
    // Helper
    static std::string GenChoicesString(std::vector<std::string>& choices);
    static int GenChoiceID(std::vector<std::string>& choices, bool includeCancel);
};

};