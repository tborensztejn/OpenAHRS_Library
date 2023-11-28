#ifndef MATRIX_H
#define MATRIX_H

#include "Common.h"

#define MATRIX_INITIALIZER { \
    .rows = 0, \
    .cols = 0, \
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
    float elements[M_MAX * N_MAX];  // All the elements of the 2D matrix in a linear array.
    bool initialized;               // This variable is used to identify whether or not a matrix has already been initialized. An uninitialized matrix cannot be manipulated.
} Matrix;

#define CreateMatrix(name) Matrix name = MATRIX_INITIALIZER

/*** Declaration of basic function prototypes for matrix manipulation. ***/

// This function is used to initialise a matrix of size (m x n) by assigning a value of 0 to each element.
Matrix InitMatrix(Matrix *Mat, const uint8_t rows, const uint8_t cols, bool *error, ErrorType *errorType);
// This function is used to assign a value to a specific element of a matrix of size (m x n).
bool SetMatrixElement(Matrix *Mat, const uint8_t row, const uint8_t col, const float value, const bool check);
// This function is used to access a specific element of a matrix of size (m x n).
float GetMatrixElement(const Matrix *const Mat, const uint8_t row, const uint8_t col, bool *error, const bool check);
// This function is used to fill an entire matrix of size (m x n) with a given value.
bool FillMatrix(Matrix *Mat, const float value, const bool check);
// This function is used to fill a square matrix of size (m x m) with the identity matrix.
bool FillIdentityMatrix(Matrix *Mat, const bool check);
// This function is used to duplicate/copy a matrix of size (m x n).
bool CopyMatrix(const Matrix *const MatA, Matrix *MatB, const bool check);
// This function is used to check if two matrices are identical/equal or not.
bool AreEqualM(const Matrix *const MatA, const Matrix *const MatB, const float deviation, bool *error, const bool check);
// This function is used to check if a matrix is square or not.
bool IsSquare(const Matrix *const Mat, bool *error, const bool check);
// This function is used to check if two matrices have the same number of rows and columns.
bool AreSameSizeM(const Matrix *const MatA, const Matrix *const MatB, bool *error, const bool check);
// This function is used to diplay a matrix of size (m x n).
bool PrintMatrix(const Matrix *const Mat, const bool check);


/*** Declarations of function prototypes of fundamental matrix calculation functions. ***/

// This function is used to perform the matrix addition operation of two matrices of size (m x n).
bool Add(const Matrix *const MatA, const Matrix *const MatB, Matrix *MatC);
// Some code here.

/*** Declaration of function prototypes for advanced matrix calculation functions. ***/
// Some code here.

#endif
