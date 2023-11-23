/********************************************************
* OpenAHRS                                              *
* $ Id: Vectors.h v1.0 21/11/2023 23:45 t.borensztejn $ *
********************************************************/

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

#ifndef VECTORS_H
#define VECTORS_H

#include "Linalg.h"

/*** Declaration of function prototypes for vector manipulation. ***/

// This function is used to initialise a vector (matrix of size (m x 1)) by assigning a value of 0 to each element.
void InitVector(float *Vect, const uint8_t m);
// This function is used to initialise a 2D vector (matrix of size (3 x 1)) by assigning x and y values to each respective element.
void Init2DVector(float Vect[2], const float x, const float y);
// This function is used to initialise a 3D vector (matrix of size (3 x 1)) by assigning x, y and z values to each respective element.
void Init3DVector(float Vect[3], const float x, const float y, const float z);
// This function is used to initialise a 4D vector (matrix of size (4 x 1)) by assigning w, x, y and z values to each respective element.
void Init4DVector(float Vect[4], const float w, const float x, const float y, const float z);
// This function is used to calculate the norm of a vector (matrix of size (m x 1)).
float Norm(const float *const Vect, const uint8_t m);
// This function is used to calculate the norm of a vector (matrix of size (3 x 1)).
float Norm3D(const float Vect[3]);
// This function is used to normalise a vector (matrix of size (m x 1)).
void NormalizeVector(float *Vect, const uint8_t m);
// This function is used to normalise a vector (matrix of size (m x 1)) while retaining the original vector.
void NormalizeVector2(const float *const Vect, float *NormalizedVect, const uint8_t m);
// This function is used to normalise a 3D vector (matrix of size (3 x 1)).
void Normalize3DVector(float Vect[3]);
// This function is used to normalise a 3D vector (matrix of size (3 x 1)) while retaining the original vector.
void Normalize3DVector2(const float Vect[3], float NormalizedVect[3]);
// This function is used to calculate the outer product of two vectors (matrices of size (m x 1)). The matrix containing the result is of size (m x m).
void OuterProduct(const float *const VectA, const float *const VectB, float *Mat, const uint8_t m);
// This function is used to calculate the dot (scalar) product of two vectors (matrices of size (m x 1)).
float DotProduct(const float *const VectA, const float *const VectB, const uint8_t m);

#endif
