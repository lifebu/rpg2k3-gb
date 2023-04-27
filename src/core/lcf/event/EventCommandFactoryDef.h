#pragma once

namespace lcf 
{

namespace ControlVariableCommand
{
    enum class Type
    {
        // change a single variable
        SINGLE_VARIABLE = 0,
        // change a range of variables
        VARIABLE_BATCH = 1,
        // use other variable as index
        VARIABLE_INDEX = 2
    };

    enum class Operation
    {
        OPERATION_SET = 0,
        OPERATION_ADD = 1,
        OPERATION_SUB = 2,
        OPERATION_MUL = 3,
        OPERATION_DIV = 4,
        OPERATION_MOD = 5
    };

    enum class OperandTypes
    {
        /*
        FirstOperand: value
        SecondOperand: Unused (=> 0)
        */
        OPERANDS_CONSTANT = 0,
        /*
        FirstOperand: value
        SecondOperand: Unused (=> 0)
        */
        OPERANDS_VARIABLE = 1,
        /*
        FirstOperand: value
        SecondOperand: Unused (=> 0)
        */
        OPERANDS_VARIABLE_ID = 2,
        /*
        Range defined by [FirstOperand, SecondOperand]
        */
        OPERANDS_RANDOM = 3,
        /*
        FirstOperand: ItemID
        SecondOperand: 0 = In Inventory, 1 = Equipped
        */
        OPERANDS_ITEM = 4,
        /*
        FirstOperand: PlayerID
        SecondOperand: 
        0 = Level, 1 = Experience, 2 = HP, 3 = MP, 4 = Maximum HP, 
        5 = Maximum MP, 6 = Attack, 7 = Defense, 8 = Mind, 9 = Agility, 
        10 = Weapon ID, 11 = Shield ID, 12 = Body ID, 13 = Head ID, 14 = Accessory ID
        */
        OPERANDS_PLAYER = 5,
        /*
        FirstOperand:
        1 - 10.000 = Event ID, 
        10.001 = Player, 10.002 = Boat, 
        10.003 = Ship, 10.004 = Airship, 
        10.005 = This Event
        SecondOperand:
        0 = Map ID, 1 = X-Coord, 
        2 = Y-Coord, 3 = Direction, 
        4 = Screen X, 5 = Screen Y
        */
        OPERANDS_EVENT = 6,
        /*
        FirstOperand: 
        0 = Money, 1 = Timer 1 Remaining Time
        2 = Party Size, 3 = Save Count
        4 = Battle Count, 5 = Win Count
        6 = Loss Count, 7 = Escape Count
        8 = MIDI Play Location (Tick)
        9 = Timer 2 Remaining Time
        SecondOperand: Unused (=> 0)
        */
        OPERANDS_OTHER = 7
    };
};

namespace ConditionalBranchCommand
{
    enum class Type
    {
        VARIABLE = 1
    };

    enum class RHSType
    {
        USE_CONSTANT = 0,
        USE_OTHER_VARIABLE = 1
    };

    enum class Comparison
    {
        EQUAL = 0,
        GREATER_OR_EQUAL = 1,
        LESS_OR_EQUAL = 2,
        GREATER = 3,
        LESS = 4,
        NOT_EQUAL = 5
    };
};

namespace ChoicesCommand
{
    enum class ChoiceCaseOnCancel
    {
        DISALLOW = 0,
        CHOICE_1 = 1,
        CHOICE_2 = 2,
        CHOICE_3 = 3,
        CHOICE_4 = 4,
        OWN_BRANCH = 5
    };
};

};