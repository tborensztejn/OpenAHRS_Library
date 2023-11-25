#ifndef LINALG_H
#define LINALG_H

#include <stdio.h>      // This includes declarations and definitions necessary for standard input/output operations in C.
//#include <stdlib.h>     // This includes declarations for functions related to dynamic memory management.
#include <stdint.h>     // This includes definitions for standard integer types with specified widths.
#include <stddef.h>     // This includes definitions related to pointer management.
#include <math.h>       // This includes declarations for standard mathematical functions in C.
#include <stdbool.h>    // This includes the necessary declarations to use the boolean data type and related constants (true and false).

// Defining a Boolean type using typedef
//typedef enum {false, true} bool;

/*
    Notes:

    To avoid the use of dynamic allocation on systems with few resources,
    such as those used in embedded systems, the dimensions of the matrix
    are fixed and capped.
*/

#define MAX_M   4   // Maximum number of rows in a matrix.
#define MAX_N   4   // Maximum number of columns in a matrix.

#define MATRIX_INITIALIZER { \
    .rows = 0, \
    .cols = 0, \
    .elements = {0}, \
    .initialized = false \
} \

#define VECTOR_INITIALIZER { \
    .rows = 0, \
    .elements = {0}, \
    .initialized = false \
} \

/*
    Notes:

    Using a structure makes the code more complex and requires more resources
    in terms of memory, but it still allows you to add verification steps
    through the various functions.
*/

typedef struct {
    uint8_t rows;                   // Number of rows in the matrix.
    uint8_t cols;                   // Number of columns in the matrix.
    float elements[MAX_M * MAX_N];  // All the elements of the 2D matrix in a linear array.
    bool initialized;               // This variable is used to identify whether or not a matrix has already been initialised. An uninitialised matrix cannot be manipulated.
} Matrix;

#define CreateMatrix(name) Matrix name = MATRIX_INITIALIZER

// A vector is matrix of size mx1.
typedef struct {
    uint8_t rows;                   // Number of rows in the vector.
    float elements[MAX_M];          // All the elements of the vector in a linear array.
    bool initialized;               // This variable is used to identify whether or not a vector has already been initialised. An uninitialised veector cannot be manipulated.
} Vector;

/*** Declaration of basic function prototypes for matrix manipulation. ***/

// This function is used to assign a value to a specific element of a matrix of size (m x n).
bool SetElement(Matrix *Mat, const uint8_t row, const uint8_t col, const float value);
// This function is used to access a specific element of a matrix of size (m x n).
float GetElement(const Matrix *const Mat, const uint8_t row, const uint8_t col, bool *error);
// This function is used to fill an entire matrix of size (m x n) with a given value.
bool FillMatrix(Matrix *Mat, const float value);
// This function is used to fill a square matrix of size (m x m) with the identity matrix.
bool FillIdentityMatrix(Matrix *Mat);
// This function is used to check is a matrix is square or not.
bool IsSquare(const Matrix *const Mat, bool *error);

bool PrintMatrix(const Matrix *const Mat);

/*** Declarations of function prototypes of fundamental matrix calculation functions. ***/


/*** Declaration of function prototypes for advanced matrix calculation functions. ***/


#endif
