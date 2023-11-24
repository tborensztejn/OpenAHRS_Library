/*******************************************************
* OpenAHRS                                             *
* $ Id: Linalg.h v1.0 21/11/2023 16:15 t.borensztejn $ *
*******************************************************/

/*
    MIT License.
    Copyright 2023 Titouan Borensztejn <borensztejn.titouan@gmail.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software
    and associated documentation files (the "Software"), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge, publish, distribute,
    sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or
    substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
    BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
    DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef LINALG_H
#define LINALG_H

/*
#include <stdio.h>      // This includes declarations and definitions necessary for standard input/output operations in C.
//#include <stdlib.h>     // his includes declarations for functions related to dynamic memory management.
#include <stdint.h>     // This includes definitions for standard integer types with specified widths.
#include <stddef.h>     // This includes definitions related to pointer management.
#include <math.h>       // This includes declarations for standard mathematical functions in C.
#include <stdbool.h>    // This includes the necessary declarations to use the boolean data type and related constants (true and false).
*/

#include "Utils.h"      // This includes various useful functions.
#include "Vectors.h"    // This includes various function to manipulate vectors.

// Defining a Boolean type using typedef
//typedef enum {false, true} bool;

/*** Declaration of basic function prototypes for matrix manipulation. ***/

// This function is used to assign a value to a specific element of a matrix of size (m x n).
void SetElement(float *Mat, const uint8_t m, const uint8_t n, const uint8_t row, const uint8_t column, const float value);
// This function is used to access a specific element of a matrix of size (m x n).
float GetElement(const float *const Mat, const uint8_t m, const uint8_t n, const uint8_t row, const uint8_t column);
// This function is used to get the index of a specific eleemnt of a matrix of size (m x n).
uint8_t Index(const uint8_t n, const uint8_t row, const uint8_t column);

/* Still in development */
// Add a description here.
//void SetRow(const float *const Mat, const uint8_t m, const uint8_t n, const uint8_t row, const float *const Vect);
// Add a description here.
//void SetColumn(const float *const Mat, const uint8_t m, const uint8_t n, const uint8_t column, const float *const Vect);
// Add a description here.
//void GetRow(const float *const Mat, const uint8_t m, const uint8_t n, const uint8_t row, float *Vect);
// Add a description here.
//void GetColumn(const float *const Mat, const uint8_t m, const uint8_t n, const uint8_t column, float *Vect);

// Add a description here.
//void AddRow();
// Add a description here.
//void AddColomun();
// Add a description here.
//void DelRow();
// Add a description here.
//void DelColumn();
// Add a description here.
//void SwapRows();
// Add a description here.
//void SwapColumns();
// Add a description here.
//void ConcatenateHorizontally();
// Add a description here.
//void ConcatenateVertically();

// This function is used to initialise a matrix of size (m x n) by assigning a value of 0 to each element.
void InitMatrix(float *Mat, const uint8_t m, const uint8_t n);
// This function is used to initialise a square matrix of size (m x m) by assigning a value of 1 to each diagonal element (identity matrix) and a value of 0 to the other elements.
void InitIdentityMatrix(float *Mat, const uint8_t m);
// This function is used to duplicate/copy a matrix of size (m x n).
void CopyMatrix(const float *const MatA, float *MatB, const uint8_t m, const uint8_t n);
// This function is used to check whether two matrices are identical/equal or not.
bool IsEqual(const float *const MatA, const float *const MatB, const uint8_t m, const uint8_t n, const float deviation);
// This function is used ti diplay a matrix of size (m x n).
void PrintMatrix(const float *const Mat, const uint8_t m, const uint8_t n);

/*** Declarations of function prototypes of fundamental matrix calculation functions. ***/

// This function is used to perform the matrix addition operation of two matrices of size (m x n).
void Add(const float *const MatA, const float *const MatB, float *MatC, const uint8_t m, const uint8_t n);
// This function is used to perform the matrix subtraction operation on two matrices of size (m x n).
void Subtract(const float *const MatA, const float *const MatB, float *MatC, const uint8_t m, const uint8_t n);
// This function is used to perform the matrix multiplication operation on two matrices of sizes (m x n) and (n x k) respectively.
// Naive implementation, as it is not very efficient for large matrices (for larger matrices, use the "divide and conquer" strategy).
void Multiply(const float *const MatA, const uint8_t mA, const uint8_t nA, const float *const MatB, const uint8_t mB, const uint8_t nB, float *MatC);
// This function is used to transpose a matrix of size (m x n).
void Transpose(float *Mat, const uint8_t m, const uint8_t n);
// This function is used to transpose a matrix of size (m x n) while preserving the original matrix.
void Transpose2(const float *const Mat, float *TransposedMat, const uint8_t m, const uint8_t n);
// This function is used to invert a square matrix of size (m x m)
bool Invert(float *Mat, const uint8_t m);
// This function is used to invert a square matrix of size (m x m) while preserving the original matrix.
bool Invert2(const float *const Mat, float *InvertedMat, const uint8_t m);
// This function is used to multiply each element of a matrix of size (m x n) by a scalar.
void MultiplyScalar(float *Mat, const uint8_t m, const uint8_t n, const float scalar);
// This function is used to multiply each element of a matrix of size (m x n) by a scalar while preserving the original matrix.
void MultiplyScalar2(const float *const Mat, float *ScaledMat, const uint8_t m, const uint8_t n, const float scalar);
// This function is used to apply an exponent to each element of a matrix of size (m x n).
void Power(float *Mat, const uint8_t m, const uint8_t n,  const int8_t exponent);
// This function is used to apply an exponent to each element of a matrix of size (m x n) while preserving the original matrix.
void Power2(const float *const Mat, float *PoweredMat, const uint8_t m, const uint8_t n,  const int8_t exponent);

/* Still in development */
// Add a description here.
//void MulRowScalar(); // Or ScaleRow();
// Add a description here.
//void MulColumnScalar()    // Or ScaleColumn();
// Add a description here.
//void IsSymetric()

/*** Declaration of function prototypes for advanced matrix calculation functions. ***/

// This function is used to determine whether a square matrix of size (m x m) is singular or not.
bool IsSingular(const float *const Mat, float *MatLU, uint8_t *pivots, const uint8_t m);
// This function calculates the trace of a matrix of size (m x n).
float Trace(float *Mat, const uint8_t m, const uint8_t n);

/*
    Notes:

    QR decomposition is a matrix decomposition designed to factor a rectangular matrix into two matrices.
    One (Q) is orthogonal (or unitary in the complex case) and the other (R) is upper triangular (or upper triangular in the complex case).
    The matrix Q is of size (m x m) and orthogonal (or unitary) which means that for the real case: Trans(Q).Q = I and for the complex case: Q*.Q = I.
    Where Trans(Q) is the transpose of Q and Q* is its transposed conjugate.
    The matrix R is upper triangular (or tri-superior) of size (m x n) which means that all elements below the main diagonal of R are zero.
*/

// This function is used to perform the QR decomposition of a matrix of size (m x n).
void DecomposeQR(const float *const Mat, float *MatQ, float *MatR, const uint8_t m, const uint8_t n);
// This function is used to check whether a matrix of size (m x n) is in row echelon form or not.
bool IsRowEchelonForm(const float *const Mat, const uint8_t m, const uint8_t n);
// Add a description here.
bool IsUpperTriangular(const float *const Mat, const uint8_t m, const uint8_t n);
// Add a description here.
bool IsLowerTriangular(const float *const Mat, const uint8_t m, const uint8_t n);
// This function is used to calculate the Frobenius norm of a matrix of size (m x n).
float CalculateFrobeniusNorm(const float *const Mat, const uint8_t m, const uint8_t n);
// This function is used to calculate the eigenvalues and eigenvectors of a general square matrix of size (m x m).
// Iterative method based on QR decomposition with shift to determine the eigenvalues and eigenvectors of a general square matrix with better convergence.
// This function is used to calculate the eigenvalues and eigenvectors of a symmetric matrix of size (m x m).
// The matrix must be square because it is symmetric.
// A symmetric matrix is equal to its transpose.
// Iterative method based on QR decomposition to determine the eigenvalues and eigenvectors of a symmetric matrix of size (m x m).
bool Eigen(const float *const Mat, const uint8_t m, float *eigenvalues, float *eigenvectors, const uint16_t niter, bool shifted);

#endif
