/********************************************************
* OpenAHRS                                              *
* $ Id: Vectors.c v1.0 21/11/2023 23:45 t.borensztejn $ *
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

#include "../includes/Vectors.h"

/*** Declaration of functions for vector manipulation. ***/

// Add an example here.
void InitVector(float *Vect, const uint8_t m) {
    // Iterate through each element and set it to zero.
    for (uint8_t row = 0; row < m; row++) {
        SetElement(Vect, m, 1, row, 0, 0.0f);
    }
}

// Add an example here.
void Init2DVector(float Vect[2], const float x, const float y) {
    SetElement(Vect, 2, 1, 0, 0, x);    // Set the first component of the vector to x.
    SetElement(Vect, 2, 1, 1, 0, y);    // Set the second component of the vector to y.
}

// Add an example here.
void Init3DVector(float Vect[3], const float x, const float y, const float z) {
    SetElement(Vect, 3, 1, 0, 0, x);    // Set the first component of the vector to x.
    SetElement(Vect, 3, 1, 1, 0, y);    // Set the second component of the vector to y.
    SetElement(Vect, 3, 1, 2, 0, z);    // Set the third component of the vector to z.
}

// Add an example here.
void Init4DVector(float Vect[4], const float w, const float x, const float y, const float z) {
    SetElement(Vect, 4, 1, 0, 0, w);    // Set the first component of the vector to w.
    SetElement(Vect, 4, 1, 1, 0, x);    // Set the second component of the vector to x.
    SetElement(Vect, 4, 1, 2, 0, y);    // Set the third component of the vector to y.
    SetElement(Vect, 4, 1, 3, 0, z);    // Set the fourth component of the vector to z.
}

// Add an example here.
float Norm(const float *const Vect, const uint8_t m) {
    float norm = 0.0f;  // Initialize the sum of squared components to zero.

    // Iterate through each element, square it, and accumulate the sum.
    for (uint8_t row = 0; row < m; row++) {
        norm += GetElement(Vect, m, 1, row, 0) * GetElement(Vect, m, 1, row, 0);
    }

    norm = sqrt(norm);  // Calculate the square root of the sum to obtain the Euclidean norm.

    // Check for numerical precision issues and set very small norms to zero.
    if (norm <= EPSILON) {
        norm = 0.0f;
    }

    return norm;    // Return the calculated Euclidean norm.
}

// Add an example here.
float Norm3D(const float Vect[3]) {
    float norm = Norm(Vect, 3);

	return norm;
}

// Add an example here.
void NormalizeVector(float *Vect, const uint8_t m) {
    float norm = Norm(Vect, m); // Calculate the Euclidean norm of the vector.

    // Check if the norm is greater than a small threshold to avoid division by zero.
    if (norm > EPSILON) {
        for (uint8_t row = 0; row < m; row++) {
            float element = GetElement(Vect, m, 1, row, 0) / norm;
            SetElement(Vect, m, 1, row, 0, element);
        }
    } else {
        // If the norm is very small or zero, set all elements to zero.
        for (uint8_t row = 0; row < m; row++) {
            SetElement(Vect, m, 1, row, 0, 0.0f);
        }
    }
}

// Add an example here.
void NormalizeVector2(const float *const Vect, float *NormalizedVect, const uint8_t m) {
    float norm = Norm(Vect, m); // Calculate the Euclidean norm of the vector.

    // Check if the norm is greater than a small threshold to avoid division by zero.
    if (norm > EPSILON) {
        // Normalize each element of the vector and store it in the new vector.
        for (uint8_t row = 0; row < m; row++) {
            float element = GetElement(Vect, m, 1, row, 0) / norm;
            SetElement(NormalizedVect, m, 1, row, 0, element);
        }
    } else {
        // If the norm is very small or zero, set all elements of the new vector to zero.
        for (uint8_t row = 0; row < m; row++) {
            SetElement(NormalizedVect, m, 1, row, 0, 0.0f);
        }
    }
}

// Add an example here.
void Normalize3DVector(float Vect[3]) {
    NormalizeVector(Vect, 3);
}

// Add an example here.
void Normalize3DVector2(const float Vect[3], float NormalizedVect[3]) {
    NormalizeVector2(Vect, NormalizedVect, 3);
}

// Add an example here.
void OuterProduct(const float *const VectA, const float *const VectB, float *Mat, const uint8_t m) {
	 Multiply(VectA, m, 1, VectB, 1, m, Mat);  // Use the Multiply function to calculate the outer product.
}

// Add an example here.
float DotProduct(const float *const VectA, const float *const VectB, const uint8_t m) {
	float dotProduct = 0.0f;   // Initialize the dot product to zero.

    // Iterate through each element, multiply corresponding elements, and accumulate the sum.
	for (uint8_t row = 0; row < m; row++) {
		dotProduct += GetElement(VectA, m, 1, row, 0) * GetElement(VectB, m, 1, row, 0);
	}

    return dotProduct;  // Return the calculated dot product.
}
