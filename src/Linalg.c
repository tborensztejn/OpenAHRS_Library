/*******************************************************
* OpenAHRS                                             *
* $ Id: Linalg.c v1.0 21/11/2023 17:20 t.borensztejn $ *
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

#include "../includes/Linalg.h"

/*** Declaration of basic functions for matrix manipulation. ***/

/*
    Example of use:

    #define M   3
    #define N   3

    //uint8_t m = 3;  // Number of rows in the matrix.
    //uint8_t n = 2;  // Number of columns in the matrix.

    float Matrix[M * N];                                        // Matrix declaration.
    //float *Matrix = (float *)malloc(m * n * sizeof(float));   // Declaration of the matrix with dynamic allocation.

    uint8_t r = 0;  // Row number of the element to be accessed.
    uint8_t c = 2;  // Column number of the element to be accessed.

    float value = 1.5f;    // Element value.

    SetElement(Matrix, m, n, r, c, value);

    // Some code here.
*/

void SetElement(float *Mat, const uint8_t m, const uint8_t n, const uint8_t row, const uint8_t column, const float value) {
    //*(Mat + row * n + column) = value;
    // No significant difference in terms of speed of execution. Modern compilers are able to perform this optimisation.
    Mat[row * n + column] = value;  // Set the value of the specified element in the matrix.
}

/*
    Example of use:

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrix.
    //uint8_t n = 2;  // Number of columns in the matrix.

    float Matrix[M * N];                                        // Matrix declaration.
    //float *Matrix = (float *)malloc(m * n * sizeof(float));   // Declaration of the matrix with dynamic allocation.

    uint8_t r = 0;  // Row number of the element to be accessed.
    uint8_t c = 2;  // Column number of the element to be accessed.

    // Some code here.

    float value = GetElement(Matrix, m, n, r, c);

    // Some code here.
*/

float GetElement(const float *const Mat, const uint8_t m, const uint8_t n, const uint8_t row, const uint8_t column) {
    float ret = Mat[row * n + column];  // Retrieve the value of the specified element from the matrix.

    return ret; // Return the value of the specified element from the matrix.
}

uint8_t Index(const uint8_t n, const uint8_t row, const uint8_t column) {
    uint8_t index = row * n + column;

    return index;
}

/*
    Example of use:

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrix.
    //uint8_t n = 2;  // Number of columns in the matrix.

    float Matrix[M * N];                                        // Matrix declaration.
    //float *Matrix = (float *)malloc(m * n * sizeof(float));   // Declaration of the matrix with dynamic allocation.

    InitMatrix(Matrix, m, n);

    // Some code here.
*/

void InitMatrix(float *Mat, const uint8_t m, const uint8_t n) {
    //memset(Mat, 0.0f, m * n * sizeof(float)); // Optimised function included in the string.h file.

    // Iterate through each element of the matrix and set it to zero.
    for (uint8_t row = 0; row < m; row++) {
        for (uint8_t column = 0; column < n; column++) {
            SetElement(Mat, m, n, row, column, 0.0f);
        }
    }
}

/*
    Example of use:

    #define M   3

    //uint8_t m = 3;  // Number of rows and columns in the matrix.

    float Matrix[M * M];                                        // Matrix declaration.
    //float *Matrix = (float *)malloc(m * m * sizeof(float));   // Declaration of the matrix with dynamic allocation.

    InitIdentityMatrix(Matrix, m);

    // Some code here.
*/

void InitIdentityMatrix(float *Mat, const uint8_t m) {
    InitMatrix(Mat, m, m);  // Initialize the matrix with zeros.

    // Set the diagonal elements to one.
    for (uint8_t i = 0; i < m; i++) {
        SetElement(Mat, m, m, i, i, 1.0f);
    }

    /*
    for (uint8_t row = 0; row < m; row++) {
        for (uint8_t column = 0; column < m; column++) {
            if (row == column) {
                SetElement(Mat, m, m, row, column, 1.0f);
            } else {
                SetElement(Mat, m, m, row, column, 0.0f);
            }
        }
    }
    */
}

/*
    Example of use:

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrices.
    //uint8_t n = 2;  // Number of columns in the matrices.

    // Matrices declaration.
    float MatrixA[M * N];
    float MatrixB[M * N];

    // Declaration of the matrices with dynamic allocation.
    //float *MatrixA = (float *)malloc(m * n * sizeof(float));
    //float *MatrixB = (float *)malloc(m * n * sizeof(float));

    // Some code here.

    CopyMatrix(MatrixA, MatrixB, m, n);

    // Some code here.
*/

void CopyMatrix(const float *const MatA, float *MatB, const uint8_t m, const uint8_t n) {
    //memcpy(MatB, MatA, m * n * sizeof(float)); // Optimised function included in the string.h file.

    // Iterate through each element and copy it from MatA to MatB.
    for (uint8_t row = 0; row < m; row++) {
        for (uint8_t column = 0; column < n; column++) {
            float element = GetElement(MatA, m, n, row, column);
            SetElement(MatB, m, n, row, column, element);
        }
    }
}

/*
    Example of use:

    #define EPSILON 0.001f

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrices.
    //uint8_t n = 2;  // Number of columns in the matrices.

    // Matrices declaration.
    float MatrixA[M * N];
    float MatrixB[M * N];

    // Declaration of the matrices with dynamic allocation.
    //float *MatrixA = (float *)malloc(m * n * sizeof(float));
    //float *MatrixB = (float *)malloc(m * n * sizeof(float));

    // Some code here.

    bool isEqual = IsEqual(MatrixA, MatrixB, m, n, EPSILON);

    // Some code here.
*/

bool IsEqual(const float *const MatA, const float *const MatB, const uint8_t m, const uint8_t n, const float deviation) {
    bool ret = true;    // Initialize the result to true.

    // Iterate through each element and check if they are close within the deviation.
    for (uint8_t row = 0; row < m; row++) {
        for (uint8_t column = 0; column < n; column++) {
            ret = CloseAll(GetElement(MatA, m, n, row, column), GetElement(MatB, m, n, row, column), deviation);
        }
    }

    return ret; // Return the result indicating whether the matrices are equal.
}

/*
    Example of use:

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrix.
    //uint8_t n = 2;  // Number of columns in the matrix.

    float Matrix[M * N];                                        // Matrix declaration
    //float *Matrix = (float *)malloc(m * n * sizeof(float));   // Declaration of the matrix with dynamic allocation.

    // Some code here.

    PrintMatrix(Matrix, m, n);
*/

void PrintMatrix(const float *const Mat, const uint8_t m, const uint8_t n) {
    // Iterate through each element and print it with a tab separator.
    for (uint8_t row = 0; row < m; row++) {
        for (uint8_t column = 0; column < n; column++) {
            //printf("%.3f ",  GetElement(Mat, m, n, row, column));
            printf("%.3f\t",  GetElement(Mat, m, n, row, column));
        }

        printf("\n");   // Move to the next row with a newline character.
    }

    printf("\n");   // Print an additional newline for better formatting.
}

/*** Declarations of functions of fundamental matrix calculation functions. ***/

/*
    Example of use:

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrices.
    //uint8_t n = 2;  // Number of columns in the matrices.

    // Matrices declaration.
    float MatrixA[M * N];
    float MatrixB[M * N];
    float MatrixC[M * N];

    // Declaration of the matrices with dynamic allocation.
    //float *MatrixA = (float *)malloc(m * n * sizeof(float));
    //float *MatrixB = (float *)malloc(m * n * sizeof(float));
    //float *MatrixC = (float *)malloc(m * n * sizeof(float));

    // Some code here.

    Add(MatrixA, MatrixB, MatrixC, m, n);

    // Some code here.
*/

void Add(const float *const MatA, const float *const MatB, float *MatC, const uint8_t m, const uint8_t n) {
    // Iterate through each element and add corresponding elements from MatA and MatB.
    for (uint8_t row = 0; row < m; row++) {
        for(uint8_t column = 0; column < n; column++) {
            float element = GetElement(MatA, m, n, row, column) + GetElement(MatB, m, n, row, column);
            SetElement(MatC, m, n, row, column, element);
        }
    }
}

/*
    Example of use:

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrices.
    //uint8_t n = 2;  // Number of columns in the matrices.

    // Matrices declaration.
    float MatrixA[M * N];
    float MatrixB[M * N];
    float MatrixC[M * N];

    // Declaration of the matrices with dynamic allocation.
    //float *MatrixA = (float *)malloc(m * n * sizeof(float));
    //float *MatrixB = (float *)malloc(m * n * sizeof(float));
    //float *MatrixC = (float *)malloc(m * n * sizeof(float));

    // Some code here.

    Subtract(MatrixA, MatrixB, MatrixC, m, n);

    // Some code here.
*/

void Subtract(const float *const MatA, const float *const MatB, float *MatC, const uint8_t m, const uint8_t n) {
    // Iterate through each element and subtract corresponding elements of MatB from MatA.
    for (uint8_t row = 0; row < m; row++) {
        for(uint8_t column = 0; column < n; column++) {
            float element = GetElement(MatA, m, n, row, column) - GetElement(MatB, m, n, row, column);
            SetElement(MatC, m, n, row, column, element);
        }
    }
}

/*
    Example of use:

    #define M   3
    #define N   2
    #define K   4

    //uint8_t m = 3;  // Number of rows in the first matrix.
    //uint8_t n = 2;  // Number of columns in the firt matrix and number of row in the second matrix
    //uint8_t k = 4;  // Number of columns in the second matrix.

    // Matrices declaration.
    float MatrixA[M * N];
    float MatrixB[N * K];
    float MatrixC[M * K];

    // Declaration of the matrices with dynamic allocation.
    //float *MatrixA = (float *)malloc(m * n * sizeof(float));
    //float *MatrixB = (float *)malloc(n * k * sizeof(float));
    //float *MatrixC = (float *)malloc(m * k * sizeof(float));

    // Some code here.

    Multiply(MatrixA, m, n, MatrixB, n, k, MatrixC);

    // Some code here.
*/

void Multiply(const float *const MatA, const uint8_t mA, const uint8_t nA, const float *const MatB, const uint8_t mB, const uint8_t nB, float *MatC) {
    // Iterate through each element of the resulting matrix.
    for (uint8_t row = 0; row < mA; row++) {
        for (uint8_t columnB = 0; columnB < nB; columnB++) {
            float element = 0.0f;

            // Multiply corresponding elements of MatA and MatB and accumulate the result.
            for (uint8_t columnA = 0; columnA < nA; columnA++) {
                element += GetElement(MatA, mA, nA, row, columnA) * GetElement(MatB, mB, nB, columnA, columnB);
            }

            // Set the calculated element in the resulting matrix.
            SetElement(MatC, mA, nB, row, columnB, element);
        }
    }
}

/*
    Example of use:

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrix.
    //uint8_t n = 2;  // Number of columns in the matrix.

    float Matrix[M * N];                                        // Matrix declaration.
    //float *Matrix = (float *)malloc(m * n * sizeof(float));   // Declaration of the matrix with dynamic allocation.

    // Some code here.

    Transpose(Matrix, m, n);

    // Some code here.
*/

void Transpose(float *Mat, const uint8_t m, const uint8_t n) {
    float TransposedMat[m * n]; // Create a temporary matrix for the transposed elements.

    //InitMatrix(TransposedMat, m, n);

    // Iterate through each element and swap the row and column indices.
    for (uint8_t row = 0; row < m; row++) {
        for (uint8_t column = 0; column < n; column++) {
            float element = GetElement(Mat, m, n, row, column);
            SetElement(TransposedMat, m, n, column, row, element);
        }
    }

    CopyMatrix(TransposedMat, Mat, m, n);   // Copy the transposed matrix back to the original matrix.
}

/*
    Example of use:

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrices.
    //uint8_t n = 2;  // Number of columns in the matrices.

    // Matrices declaration.
    float MatrixA[M * N];
    float MatrixB[M * N];

    // Declaration of the matrices with dynamic allocation.
    //float *MatrixA = (float *)malloc(m * n * sizeof(float));
    //float *MatrixB = (float *)malloc(m * n * sizeof(float));

    // Some code here.

    Transpose2(MatrixA, MatrixB, m, n);

    // Some code here.
*/

void Transpose2(const float *const Mat, float *TransposedMat, const uint8_t m, const uint8_t n) {
    // Iterate through each element and swap the row and column indices.
    for (uint8_t row = 0; row < m; row++) {
        for (uint8_t column = 0; column < n; column++) {
            float element = GetElement(Mat, m, n, row, column);
            SetElement(TransposedMat, m, n, column, row, element);
        }
    }
}

/*
    Example of use:

    #define M   3

    //uint8_t m = 3;  // Number of rows and columns in the matrix.

    float Matrix[M * M];                                        // Matrix declaration.
    //float *Matrix = (float *)malloc(m * m * sizeof(float));   // Declaration of the matrix with dynamic allocation.

    // Some code here.

    bool error = Invert(Matrix, m);

    // Some code here.
*/

bool Invert(float *Mat, const uint8_t m) {
    float ret = true;

    float InvertedMat[m * m];

    InitIdentityMatrix(InvertedMat, m);

    for (uint8_t row = 0; row < m; row++) {
        float pivot = GetElement(Mat, m, m, row, row);

        if (fabsf(pivot) < EPSILON) {
            ret = false;

            break;
        } else {
            if (fabsf(pivot - 1.0f) > EPSILON) {
                for (uint8_t column = 0; column < m; column++) {
                    float element = GetElement(Mat, m, m, row, column) / pivot;
                    SetElement(Mat, m, m, row, column, element);
                    element = GetElement(InvertedMat, m, m, row, column) / pivot;
                    SetElement(InvertedMat, m, m, row, column, element);
                }
            }

            for (uint8_t k = 0; k < m; k++) {
                if (k != row) {
                    float ratio = GetElement(Mat, m, m, k, row);

                    for (uint8_t column = 0; column < m; column++) {
                        float element = GetElement(Mat, m, m, row, column) * ratio;
                        element = GetElement(Mat, m, m, k, column) - element;
                        SetElement(Mat, m, m, k, column, element);

                        element = GetElement(InvertedMat, m, m, row, column) * ratio;
                        element = GetElement(InvertedMat, m, m, k, column) - element;
                        SetElement(InvertedMat, m, m, k, column, element);
                    }
                }
            }
        }
    }

    CopyMatrix(InvertedMat, Mat, m, m);

    return ret;
}

/*
    Example of use:

    #define M   3

    //uint8_t m = 3;  // Number of rows and columns in the matrices.

    // Matrices declaration.
    float MatrixA[M * M];
    float MatrixB[M * M];

    // Declaration of the matrices with dynamic allocation.
    //float *MatrixA = (float *)malloc(m * m * sizeof(float));
    //float *MatrixB = (float *)malloc(m * m * sizeof(float));

    // Some code here.

    Invert2(MatrixA, MatrixB, m);

    // Some code here.
*/

bool Invert2(const float *const Mat, float *InvertedMat, const uint8_t m) {
    float CopiedMat[m * m];

    CopyMatrix(Mat, CopiedMat, m, m);
    InitIdentityMatrix(InvertedMat, m);

    for (uint8_t row = 0; row < m; row++) {
        float pivot = GetElement(CopiedMat, m, m, row, row);

        if (fabsf(pivot) < EPSILON) {
            break;
        } else {
            for (uint8_t column = 0; column < m; column++) {
                float element = GetElement(CopiedMat, m, m, row, column) / pivot;
                SetElement(CopiedMat, m, m, row, column, element);
                element = GetElement(InvertedMat, m, m, row, column) / pivot;
                SetElement(InvertedMat, m, m, row, column, element);
            }

            for (uint8_t k = 0; k < m; k++) {
                if (k != row) {
                    float ratio = GetElement(CopiedMat, m, m, k, row);

                    for (uint8_t column = 0; column < m; column++) {
                        float element = GetElement(CopiedMat, m, m, row, column) * ratio;
                        element = GetElement(CopiedMat, m, m, k, column) - element;
                        SetElement(CopiedMat, m, m, k, column, element);

                        element = GetElement(InvertedMat, m, m, row, column) * ratio;
                        element = GetElement(InvertedMat, m, m, k, column) - element;
                        SetElement(InvertedMat, m, m, k, column, element);
                    }
                }
            }
        }
    }
}

/*
    Example of use:

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrix.
    //uint8_t n = 2;  // Number of columns in the matrix.

    float Matrix[M * N];                                        // Matrix declaration
    //float *Matrix = (float *)malloc(m * n * sizeof(float));   // Declaration of the matrix with dynamic allocation.

    // Some code here.

    float factor = 2.0f;

    MultiplyScalar(Matrix, m, n, factor);
*/

void MultiplyScalar(float *Mat, const uint8_t m, const uint8_t n, const float scalar) {
        // Iterate through each element and multiply it by the scalar.
        for (uint8_t row = 0; row < m; row++) {
                for (uint8_t column = 0; column < n; column++) {
                        float element = GetElement(Mat, m, n, row, column) * scalar;
                        SetElement(Mat, m, n, row, column, element);
                }
        }
}

/*
    Example of use:

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrices.
    //uint8_t n = 2;  // Number of columns in the matrices.

    // Matrices declaration.
    float MatrixA[M * N];
    float MatrixB[M * N];

    // Declaration of the matrices with dynamic allocation.
    //float *MatrixA = (float *)malloc(m * n * sizeof(float));
    //float *MatrixB = (float *)malloc(m * n * sizeof(float));

    // Some code here.
    float factor = 2.0f;

    MultiplyScalar2(MatrixA, MatrixB, m, n, factor);

    // Some code here.
*/

void MultiplyScalar2(const float *const Mat, float *ScaledMat, const uint8_t m, const uint8_t n, const float scalar) {
    // Some code here.
}

/*
    Example of use:

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrix.
    //uint8_t n = 2;  // Number of columns in the matrix.

    float Matrix[M * N];                                        // Matrix declaration
    //float *Matrix = (float *)malloc(m * n * sizeof(float));   // Declaration of the matrix with dynamic allocation.

    // Some code here.

    float exponent = 2.0f;

    Power(Matrix, m, n, exponent);
*/

void Power(float *Mat, const uint8_t m, const uint8_t n,  const int8_t exponent) {
    // Iterate through each element of the matrix.
    for (uint8_t row = 0; row < m; row++) {
        for (uint8_t column = 0; column < n; column++) {
            // Get the current element from the matrix.
            float element = GetElement(Mat, m, n, row, column);
            // Raise the element to the specified exponent using the power function.
            //element = Pow(element, exponent);
            element = powf(element, (float)exponent);
            // Set the modified element back to the matrix.
            SetElement(Mat, m, n, row, column, element);
        }
    }
}

/*
    Example of use:

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrices.
    //uint8_t n = 2;  // Number of columns in the matrices.

    // Matrices declaration.
    float MatrixA[M * N];
    float MatrixB[M * N];

    // Declaration of the matrices with dynamic allocation.
    //float *MatrixA = (float *)malloc(m * n * sizeof(float));
    //float *MatrixB = (float *)malloc(m * n * sizeof(float));

    // Some code here.
    float exponent = 2.0f;

    Power2(MatrixA, MatrixB, m, n, exponent);

    // Some code here.
*/

void Power2(const float *const Mat, float *PoweredMat, const uint8_t m, const uint8_t n,  const int8_t exponent) {
    // Some code here.
}

/*** Declaration of functions for advanced matrix calculation functions. ***/

/*
    Example of use:

    #define M   3

    //uint8_t m = 3;  // Number of rows and columns in the matrix.

    float Matrix[M * M];                                        // Matrix declaration.
    //float *Matrix = (float *)malloc(m * m * sizeof(float));   // Declaration of the matrix with dynamic allocation.

    // Some code here.

    bool isSingular = Invert(Matrix, m);

    // Some code here.
*/

// Add an example here.
bool IsSingular(const float *const Mat, float *MatLU, uint8_t *pivots, const uint8_t m) {
    bool ret = 0;

    if (!IsEqual(Mat, MatLU, m, m, EPSILON)) {
        CopyMatrix(Mat, MatLU, m, m);
    }

    // Create the pivot vector.
    for (uint8_t row = 0; row < m; row++) {
        pivots[row] = row;
    }

    for (uint8_t row = 0; row < m - 1; row++) {
        uint8_t maxIndex = row;

        for (uint8_t column = row + 1; column < m; column++) {
            //if (fabsf(GetElement(MatLU, m, m, pivots[column], row)) > fabsf(GetElement(MatLU, m, m, pivots[maxIndex], row))) {
            if (fabsf(MatLU[m * pivots[column] + row]) > fabsf(MatLU[m * pivots[maxIndex] + row])) {
                maxIndex = column;
            }
        }

        uint8_t pivotMem = pivots[row];
        pivots[row] = pivots[maxIndex];
        pivots[maxIndex] = pivotMem;

        //if (fabsf(GetElement(MatLU, m, m, pivots[row], row)) < EPSILON) {
        if (fabsf(MatLU[m * pivots[row] + row]) < EPSILON) {
            // The matrix is singular.
            ret = true;

            break;
        } else {
            for (uint8_t column = row + 1; column < m; column++) {
                /*
                float element = GetElement(MatLU, m, m, pivots[column], row) / GetElement(MatLU, m, m, pivots[row], row);
                SetElement(MatLU, m, m, pivots[column], row, element);
                */

                MatLU[m * pivots[column] + row] = MatLU[m * pivots[column] + row] / MatLU[m * pivots[row] + row];

                for (uint8_t k = row + 1; k < m; k++) {
                    /*
                    element = GetElement(MatLU, m, m, pivots[column], k);
                    element = element - GetElement(MatLU, m, m, pivots[row], k) * GetElement(MatLU, m, m, pivots[column], row);
                    */

                    MatLU[m * pivots[column] + k] = MatLU[m * pivots[column] + k] - MatLU[m * pivots[row] + k] * MatLU[m * pivots[column] + row];
                }
            }
        }
    }

    return ret;
}

/*
    Example of use:

    #define M   3
    #define N   2

    //uint8_t m = 3;  // Number of rows in the matrix.
    //uint8_t n = 2;  // Number of columns in the matrix.

    float Matrix[M * N];                                        // Matrix declaration
    //float *Matrix = (float *)malloc(m * n * sizeof(float));   // Declaration of the matrix with dynamic allocation.

    // Some code here.

    float trace = Trace(Matrix, m, n);
*/

float Trace(float *Mat, const uint8_t m, const uint8_t n) {
    float trace = 0.0f; // Initialize trace to zero.

    // / Loop through the minimum of m and n and accumulate diagonal elements to trace.
    for (uint8_t i = 0; i < Min(m, n); i++) {
        // // Add the element at position (i, i) to the trace.
        trace += GetElement(Mat, m, n, i, i);
    }

    // Return the computed trace.
    return trace;
}

// Add an example here.
void DecomposeQR(const float *const Mat, float *MatQ, float *MatR, const uint8_t m, const uint8_t n) {
    CopyMatrix(Mat, MatQ, m, n);     // Duplicate the original matrix.

    // Apply the Gram-Schmidt method to orthogonalise the columns and obtain the Q matrix.
    for (uint8_t column = 0; column < n; column++) {
        for (uint8_t row = 0; row < column; row++) {
            float dotProduct = 0.0f;

            for (uint8_t k = 0; k < m; k++) {
                dotProduct += GetElement(MatQ, m, n, k, row) * GetElement(Mat, m, n, k, column);
            }

            for (uint8_t k = 0; k < m; k++) {
                float element = GetElement(MatQ, m, n, k, column) - dotProduct * GetElement(MatQ, m, n, k, row);
                SetElement(MatQ, m, n, k, column, element);
            }
        }

        // Normalise de column.
        float norm = 0.0f;

        for (uint8_t k = 0; k < m; k++) {
            norm += GetElement(MatQ, m, n, k, column) * GetElement(MatQ, m, n, k, column);
        }

        norm = sqrt(norm);

        if (norm > EPSILON) {
            for (uint8_t k = 0; k < m; k++) {
                float element = GetElement(MatQ, m, n, k, column) / norm;
                SetElement(MatQ, m, n, k, column, element);
            }
        } else {
            // Some code here.

            break;
        }
    }

    // Duplicate Q matrix.
    float CopiedMatQ[m * n];
    CopyMatrix(MatQ, CopiedMatQ, m, n);
    Transpose(CopiedMatQ, m, n);
    Multiply(CopiedMatQ, m, n, Mat, m, n, MatR);
}

// Add an example here.
bool IsRowEchelonForm(const float *const Mat, const uint8_t m, const uint8_t n) {
    bool ret = false;

    // Some code here.

    return ret;

}

// Add an example here.
bool IsUpperTriangular(const float *const Mat, const uint8_t m, const uint8_t n) {
    // Loops on every line except the first (which doesn't need to have null elements).
	float sum = 0.0f;

    for (uint8_t row = 1; row < m; ++row) {
        // We loop over the columns corresponding to the lower triangular matrix as a function of the current row.
        for (uint8_t column = 0; column < row; ++column) {
			// Add this item to the cumulative sum.
            sum += GetElement(Mat, m, n, row, column);
        }
    }

    // If the matrix is upper diagonal, the cumulative sum must always be zero, otherwise the matrix cannot be upper diagonal.
    uint8_t ret = CloseAll(sum, 0.0f, EPSILON);

    // Add the other conditions here.

	return ret;
}

// Add an example here.
bool IsLowerTriangular(const float *const Mat, const uint8_t m, const uint8_t n) {
    bool ret = false;

    // Some code here.

    return ret;
}

// Add an example here.
float CalculateFrobeniusNorm(const float *const Mat, const uint8_t m, const uint8_t n) {
    float frobeniusNorm = 0.0f; // Initialize the sum of squared elements to zero.

    // Iterate through each element, square it, and accumulate the sum.
    for (uint8_t row = 0; row < m; row++) {
        for (uint8_t column = 0; column < n; column++) {
            frobeniusNorm += GetElement(Mat, m, n, row, column) * GetElement(Mat, m, n, row, column);
        }
    }

    frobeniusNorm = sqrt(frobeniusNorm);    // Calculate the square root of the sum to obtain the Frobenius norm.

    return frobeniusNorm;   // Return the calculated Frobenius norm.
}

// Add an example here.
bool Eigen(const float *const Mat, const uint8_t m, float *eigenvalues, float *eigenvectors, const uint16_t niter, bool shifted) {
    // Initialize variables and matrices for the algorithm.
    bool ret = false;;

    float MatA[m * m];
    float MatI[m * m];
    float MatQ[m * m];
    float MatR[m * m];
    float previousEigenvalues[m];
    float deltaEigenvalues[m];

    float s = 0.0f;
    float relativeVariation = 0.0f;

    CopyMatrix(Mat, MatA, m, m);    // Copy the input matrix to avoid modification.
    InitIdentityMatrix(MatI, m);    // Initialise an identity matrix.
    InitMatrix(MatQ, m, m);         // Initialise the Q matrix.
    //InitIdentityMatrix(MatQ, m);  // Initialise the Q matrix as an identity matrix.
    InitMatrix(MatR, m, m);         // Initialise the R matrix.
    InitVector(previousEigenvalues, m);
    InitVector(deltaEigenvalues, m);
    InitIdentityMatrix(eigenvectors, m);

    for (uint32_t iter = 0; iter < niter; iter++) {
        if (shifted) {
            // Apply Wilkinson shift method to determine the shift.
            float a = GetElement(MatA, m, m, m - 2, m - 2);
            float b = GetElement(MatA, m, m, m - 2, m - 1);
            float c = GetElement(MatA, m, m, m - 1, m - 1);

            float delta = ((a - c) / 2.0f) * ((a - c) / 2.0f) + b * b;

            if (a < c) {
                s = c - delta / (fabsf(b) + sqrt(delta));
            } else {
                s = c + delta / (fabsf(b) + sqrt(delta));
            }

            //Q, R = qr_decomposition(A - s*I)
            //A = R*Q + s*I

            // Apply QR decomposition with shift.
            float MatTemp[m * m];
            // InitMatrix(MatTemp, m, m);
            MultiplyScalar(MatI, m, m, s);
            Subtract(MatA, MatI, MatTemp, m, m);
            CopyMatrix(MatTemp, MatA, m, m);
            DecomposeQR(MatA, MatQ, MatR, m, m);

            // Perform the matrix product of the R matrix and the Q matrix with shift.
            Multiply(MatR, m, m, MatQ, m, m, MatTemp);
            Add(MatTemp, MatI, MatA, m, m);
            InitIdentityMatrix(MatI, m);    // Initialise an identity matrix.
        } else {
            // Apply regular QR decomposition.
            DecomposeQR(MatA, MatQ, MatR, m, m);
            // Perform the matrix product of the R matrix and the Q matrix.
            float MatTemp[m * m];
            Multiply(MatR, m, m, MatQ, m, m, MatTemp);
            // Duplicate the result (matrix obtained by the previous matrix operation) in the matrix (copy).
            CopyMatrix(MatTemp, MatA, m, m);
        }

        // Find eigenvectors.
        float _eigenvectors[m * m];
        Multiply(eigenvectors, m, m, MatQ, m, m, _eigenvectors);
        CopyMatrix(_eigenvectors, eigenvectors, m, m);

        // If the algorithm has converged before reaching the maximum number of iterations, no error.
        // If the maximum number of iterations is reached before converging, error.

        // Extract the eigenvalues from the diagonal of the matrix.
        for (uint8_t k = 0; k < m; k++) {
            float eigenvalue = GetElement(MatA, m, m, k, k);
            eigenvalues[k] = eigenvalue;
        }

        // Calculate the relative variation in eigenvalues.
        Subtract(eigenvalues, previousEigenvalues, deltaEigenvalues, m, 1);
        relativeVariation = Norm(deltaEigenvalues, m) / Norm(eigenvalues, m);

        // Check for convergence.
        if (relativeVariation < EPSILON) {
            ret = true;

            /*
            printf("Number of iterations performed: %d\n", iter);
            printf("Relative variation: %f\n", relativeVariation);
            printf("Convergence: OK");
            */

            //AfficherMatrice(MatA, m, m);

            break;
        } else {
            // Update the previous eigenvalues for the next iteration.
            for (uint8_t k = 0; k < m; k++) {
                eigenvalues[k] = 0.0f;
                float eigenvalue = GetElement(MatA, m, m, k, k);
                previousEigenvalues[k] = eigenvalue;
                //printf("Convergence: NOK.\n\n");
            }
        }
    }

    return ret; // Return the convergence status.
}
