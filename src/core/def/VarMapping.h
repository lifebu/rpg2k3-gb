#pragma once

// this will be used to generate the variable names in RPG Maker.
#define GET_VARIABLE_NAME(Variable) (#Variable)

// Defines the mapping of the variables used in RPG Maker.
enum class VARMAPPING : int
{
    BYTE_OFFSET_ID = 1,
    LABEL_ID = 2,
    // TODO: When I add VARS_PER_LABEL as a parameters this needs a dynamic amount of statically mapped variables.
    READ_VAR_1 = 3,
    // Second Variable is overhead (overlap) for the case that a 2-Byte R/W Op needs the last Byte of the first Var and the next byte.
    READ_VAR_2 = 4,
    
    COUNT
};

static const char* VARMAPPING_NAMES[] = 
{
    "", 
    "BYTE_OFFSET_ID", 
    "LABEL_ID", 
    "READ_VAR_1", 
    "READ_VAR_2"
};