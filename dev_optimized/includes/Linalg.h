#ifndef LINALG_H
#define LINALG_H

#include "Matrix.h"
#include "Vector.h"

/*** Declaration of basic function prototypes for the combined manipulation of vectors and matrices. ***/

// This function is used to set a specific row in a matrix of size (m x n) using the values provided in a vector (m x 1).
bool SetRow(Matrix *Mat, const Vector *const Vect, const uint8_t row);
bool GetRow(const Matrix *const Mat, Vector *Vect, const uint8_t row);

/*** Declaration of fundamental function prototypes for combined vector and matrix calculation operations. ***/
// Some code here.

/*** Declaration of advanced function prototypes for combined vector and matrix calculation operations. ***/
// Some code here.

#endif
