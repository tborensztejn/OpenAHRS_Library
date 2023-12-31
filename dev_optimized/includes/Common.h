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

typedef enum {
    NO_ERROR,
    NULL_PTR,
    UNINITIALIZED,
    ALREADY_INIT,
    INVALID_ROWS_NUMBER,
    INVALID_COLS_NUMBER,
    NON_EXISTING_ROW,
    NON_EXISTING_COL,
    SIZE_MISMATCH,
    INVALID_VALUE,
    INVALID_ELEMENT
} ErrorType;

/*
    Notes:

    A number of checks are carried out to ensure correct operation.
    Some steps may be redundant. To optimise operation, they can be deactivated.
*/

#define ROUTINE_CHECK       1   // Enables routine verification steps.
#define NO_ROUTINE_CHECK    0   // Disables routine verification steps.

/*
    Notes:

    To avoid the use of dynamic allocation on systems with few resources,
    such as those used in embedded systems, the dimensions of the matrix
    and the vector are fixed and capped.
*/

#define M_MAX   4       // Maximum number of rows in a matrix and a vector.
#define N_MAX   4       // Maximum number of columns in a matrix.

/*** Declaration of function prototypes. ***/

// This function is used to check if the rows number is valid (rows number less than or equal to M_MAX) to avoid buffer overflow.
bool IsValidRowsNumber(const uint8_t rows);
// This function is used to check if the columns number is valid (colums number less than or equal to N_MAX) to avoid buffer overflow.
bool IsValidColsNumber(const uint8_t cols);
// This function is used to check if the index is valid (row number less than number of rows) to avoid buffer overflow.
bool IsValidRow(const uint8_t row, const uint8_t rows);
// This function is used to check if the index is valid (column number less than number of columns) to avoid buffer overflow.
bool IsValidCol(const uint8_t col, const uint8_t cols);

#endif
