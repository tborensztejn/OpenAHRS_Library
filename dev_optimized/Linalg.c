#include "Linalg.h"
#include "../includes/Utils.h"

// Add an example here.
Matrix InitMatrix(Matrix *Mat, const uint8_t rows, const uint8_t cols) {
    if (Mat != NULL) {
        if (!Mat->initialized) {
            Mat->rows = rows;
            Mat->cols = cols;
            Mat->initialized = true;
        } else {
            // The matrix passed as a parameter to the function via a pointer has already been initialized.
            // Some code here.
        }
    } else {
        //Matrix NewMatrix = MATRIX_INITIALIZER;
        CreateMatrix(NewMatrix);

        NewMatrix.rows = rows;
        NewMatrix.cols = cols;
        NewMatrix.initialized = true;

        return NewMatrix;
    }
}

// Add an example here.
bool SetElement(Matrix *Mat, const uint8_t row, const uint8_t col, const float value) {
    bool error = true;

    // If the pointer is not NULL.
    if (Mat != NULL) {
        // If the matrix is initialized.
        if (Mat->initialized) {
            Mat->elements[row * Mat->cols + col] = value;   // Set the value of the specified element in the matrix.
            error = false;
        } else {
            // Some code here.
        }
    } else {
        // Some code here.
    }

    return error;
}

// Add an example here.
float GetElement(const Matrix *const Mat, const uint8_t row, const uint8_t col) {
    float element;  // Declare the variable that will store the returned value.

    // If the pointer is not NULL.
    if (Mat != NULL) {
        // If the matrix is initialized.
        if (Mat->initialized) {
            element = Mat->elements[row * Mat->cols + col];   // Retrieve the value of the specified element from the matrix.
        } else {
            element = NAN;
        }
    } else {
        element = NAN;
    }

    return element; // Return the value of the specified element from the matrix.
}

// Add an example here.
void FillMatrix(Matrix *Mat, const float value) {
    if (Mat->initialized) {
        for (uint8_t row = 0; row < Mat->rows; row++) {
            for (uint8_t col = 0; col < Mat->cols; col++) {
                SetElement(Mat, row, col, value);
            }
        }
    } else {
        // Some code here.
    }
}

int main() {
    const uint8_t rows = 3;
    const uint8_t cols = 3;

    Matrix Mat1 = InitMatrix(NULL, rows, cols);
    printf("%d\n", Mat1.initialized);
    CreateMatrix(Mat2);
    InitMatrix(&Mat2, rows, cols);
    printf("%d\n", Mat2.initialized);

    // Some code here.

    return 0;
}
