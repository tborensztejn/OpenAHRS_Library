#ifndef VECTOR_H
#define VECTOR_H

#include "Common.h"

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

// A vector is matrix of size mx1.
typedef struct {
    uint8_t rows;                   // Number of rows in the vector.
    float elements[M_MAX];          // All the elements of the vector in a linear array.
    bool initialized;               // This variable is used to identify whether or not a vector has already been initialized. An uninitialized veector cannot be manipulated.
} Vector;

#define CreateVector(name) Vector name = VECTOR_INITIALIZER

/*** Declaration of basic function prototypes for vector manipulation. ***/

// This function is used to initialise a vector of size (m x 1) by assigning a value of 0 to each element.
Vector InitVector(Vector *Vect, const uint8_t rows, bool *error, ErrorType *errorType);
// Add description here.
bool ApplyRoutineVectorChecks(const Vector *const Vect, ErrorType *errorType, const uint8_t *const row);
// This function is used to assign a value to a specific element of a vector of size (m x 1).
bool SetVectorElement(Vector *Vect, const uint8_t row, const float value, ErrorType *errorType, const bool check);
// This function is used to access a specific element of a vector of size (m x 1).
float GetVectorElement(const Vector *const Vect, const uint8_t row, bool *error, ErrorType *errorType, const bool check);
// This function is used to fill an entire vector of size (m x 1) with a given value.
bool FillVector(Vector *Vect, const float value, ErrorType *errorType, const bool check);
// This function is used to duplicate/copy a vector of size (m x 1).
bool CopyVector(const Vector *const VectA, Vector *VectB, ErrorType *errorType, const bool check);
// This function is used to check if two vectors are identical/equal or not.
bool AreEqualV(const Vector *const VectA, const Vector *const VectB, const float deviation, bool *error, ErrorType *errorType, const bool check);
// This function is used to check if two vectors have the same number of rows.
bool AreSameSizeV(const Vector *const VectA, const Vector *const VectB, bool *error, ErrorType *errorType, const bool check);
// This function is used to diplay a vector of size (m x 1).
bool PrintVector(const Vector *const Vect, ErrorType *errorType, const bool check);

/*** Declarations of function prototypes of fundamental vector calculation functions. ***/
// Some code here.

/*** Declaration of function prototypes for advanced vector calculation functions. ***/
// Some code here.

#endif
