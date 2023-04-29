#pragma once

namespace lcf 
{

namespace ControlVariable
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

namespace ConditionalBranch
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

namespace Choices
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

namespace ChangeItem
{
    enum class Operation
    {
        INCREASE = 0,
        DECREASE = 1
    };

    enum class ItemIDType
    {
        FIXED_ITEM_ID,
        VARIABLE_ID
    };

    enum class OperandType
    {
        CONSTANT = 0,
        VARIABLE = 0
    };
};

namespace ChangePartyMember
{
    enum class Operation
    {
        ADD = 0,
        REMOVE = 1
    };

    enum class ActorIDType
    {
        FIXED_ITEM_ID,
        VARIABLE_ID
    };
};

namespace ChangeExp
{
    enum class ActorRange
    {
        ENTIRE_PARTY = 0,
        FIXED_ID = 1,
        VARIABLE_ID = 2
    };

    enum class Operation
    {
        INCREASE = 0,
        DECREASE = 1
    };

    enum class Operand
    {
        CONSTANT = 0,
        VALUE = 1
    };

    enum class ShowLevelUp
    {
        DONT_SHOW = 0,
        SHOW_LEVEL_UP = 1
    };
};

namespace ChangeParam
{
    enum class ActorRange
    {
        ENTIRE_PARTY = 0,
        FIXED_ID = 1,
        VARIABLE_ID = 2
    };

    enum class Operation
    {
        INCREASE = 0,
        DECREASE = 1
    };

    enum class Parameter
    {
        MAX_HP = 0,
        MAX_MP = 1,
        ATTACK = 2,
        DEFENSE = 3,
        MIND = 4,
        AGILITY = 5
    };

    enum class Operand
    {
        CONSTANT = 0,
        VALUE = 1
    };
};

namespace ChangeEquip
{
    enum class ActorRange
    {
        ENTIRE_PARTY = 0,
        FIXED_ID = 1,
        VARIABLE_ID = 2
    };

    enum class Operation
    {
        CHANGE_EQUIPMENT = 0,
        REMOVE_EQUIPMENT = 1
    };

    enum class ItemIDType
    {
        FIXED_ID = 0,
        VARIABLE_ID = 1
    };

    enum class Item
    {
        UNEQUIP_WEAPON = 0,
        UNEQUIP_SHIELD = 1,
        UNEQUIP_BODY = 2,
        UNEQUIP_HEAD = 3,
        UNEQUIP_ACCESSORY = 4,
        UNEQUIP_ALL = 5
    };
};

namespace SetEventLocation
{
    enum class EventIDType
    {
        EVENT_ID = 0,
        THIS_EVENT_ID = 10005
    };

    enum class LocationType
    {
        CONSTANT = 0,
        VARIABLE_IDS = 1
    };

    enum class DIRECTION
    {
        RETAIN = 0,
        UP = 1,
        RIGHT = 2,
        DOWN = 3,
        LEFT = 4
    };
};

namespace GetEventID
{
    enum class LocationType
    {
        CONSTANT = 0,
        VARIABLE_ID = 1
    };
};

namespace CallEvent
{
    enum class EventType
    {
        COMMON_EVENT = 0,
        CONST_MAP_EVENT = 1,
        VARIABLE_MAP_EVENT = 2
    };
};

namespace ShowHidePlayer
{
    enum class Visibility
    {
        INVISIBLE = 0,
        VISIBLE = 1
    };
};

namespace ShowPicture
{
    enum class PictureIDType
    {
        CONSTANT = 0,
        VARIABLE_ID = 1
    };

    enum class PosType
    {
        CONSTANT = 0,
        VARIABLE_ID = 1
    };
};

};