#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>      // This includes declarations and definitions necessary for standard input/output operations in C.
//#include <stdlib.h>     // This includes declarations for functions related to dynamic memory management.
#include <stdint.h>     // This includes definitions for standard integer types with specified widths.
#include <stddef.h>     // This includes definitions related to pointer management.
#include <math.h>       // This includes declarations for standard mathematical functions in C.
#include <stdbool.h>    // This includes the necessary declarations to use the boolean data type and related constants (true and false).

#include "../../includes/Utils.h"

// Defining a Boolean type using typedef
//typedef enum {false, true} bool;

/*
    Notes:

    A number of checks are carried out to ensure correct operation.
    Some steps may be redundant. To optimise operation, they can be deactivated.
*/

#define CHECK       1   // Enables verification steps.
#define NO_CHECK    0   // Disables verification steps.

/*
    Notes:

    To avoid the use of dynamic allocation on systems with few resources,
    such as those used in embedded systems, the dimensions of the matrix
    and the vector are fixed and capped.
*/

#define MAX_M   4       // Maximum number of rows in a matrix and a vector.
#define MAX_N   4       // Maximum number of columns in a matrix.

/*** Declaration of function prototypes. ***/

// This function is used to check if the index is valid (row number less than or equal to MAX_M) to avoid buffer overflow.
bool IsValidRow(const uint8_t row);
// This function is used to check if the index is valid (colum number less than or equal to MAX_N) to avoid buffer overflow.
bool IsValidCol(const uint8_t col);

#endif
