#pragma once

// this will be used to generate the variable names in RPG Maker.
#define GET_VARIABLE_NAME(Variable) (#Variable)

// Defines the mapping of the variables used in RPG Maker.
namespace VARMAPPING {
    const static int BYTE_OFFSET_ID = 1;
    const static int LABEL_ID = 2;
    const static int READ_VAR_1 = 3;
    // Second Variable is overhead for the case that a 2-Byte R/W Op needs the last Byte of the first Var and the next byte.
    const static int READ_VAR_2 = 4;
};