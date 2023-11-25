#include "Linalg.h"
#include "../includes/Utils.h"

// Add an example here.
Matrix InitMatrix(Matrix *Mat, const uint8_t rows, const uint8_t cols) {
    // Check if the pointer is not null.
    if (Mat != NULL) {
        // Check if the matrix has already been initialized.
        if (!Mat->initialized) {
            Mat->rows = rows;
            Mat->cols = cols;
            Mat->initialized = true;
        } else {
            // The matrix passed as a parameter to the function via a pointer has already been initialized.
            // Some code here.
        }
    } else {
        // The pointer is null.
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
    bool error = true;  // Initialize the error to true.

    // Check if the pointer is not null.
    if (Mat != NULL) {
        // Check if the matrix is initialized.
        if (Mat->initialized) {
            // Check if the value is valid.
            if (value != NAN) {
                Mat->elements[row * Mat->cols + col] = value;   // Set the value of the specified element in the matrix.
                error = false;
            }
        } else {
            // The matrix is not initialized.
            // Some code here.
        }
    } else {
        // The pointer is null.
        // Some code here.
    }

    return error;
}

// Add an example here.
float GetElement(const Matrix *const Mat, const uint8_t row, const uint8_t col, bool *error) {
    float element;  // Declare the variable that will store the returned value.
    *error = true;  // Initialize the error to true.

    // Check if the pointer is not null.
    if (Mat != NULL) {
        // Check if the matrix is initialized.
        if (Mat->initialized) {
            element = Mat->elements[row * Mat->cols + col];   // Retrieve the value of the specified element from the matrix.
            *error = false;
        } else {
            // The matrix is not initialized.
            element = NAN;
        }
    } else {
        // The pointer is null.
        element = NAN;
    }

    return element; // Return the value of the specified element from the matrix.
}

// Add an example here.
bool FillMatrix(Matrix *Mat, const float value) {
    bool error = true;  // Initialize the error to true.

    // Check if the pointer is not null.
    if (Mat != NULL) {
        // Check if the matrix is initialized.
        if (Mat->initialized) {
            // Assign the value to each element of the matrix.
            for (uint8_t row = 0; row < Mat->rows; row++) {
                for (uint8_t col = 0; col < Mat->cols; col++) {
                    error = SetElement(Mat, row, col, value);
                }
            }
        } else {
            // The matrix is not initialized.
            // Some code here.
        }
    } else {
        // The pointer is null.
        // Some code here.
    }

    return error;
}

// Add an example here.
bool FillIdentityMatrix(Matrix *Mat) {
    bool error = true;  // Initialize the error to true.

    // Check if the pointer is not null.
    if (Mat != NULL) {
        // Check if the matrix is initialized.
        if (Mat->initialized) {
            // Check if the matrix is square.
            if (IsSquare(Mat, &error)) {
                if (!error) {
                    // Set the diagonal elements to one.
                    for (uint8_t row = 0; row < Mat->rows; row++) {
                        for (uint8_t col = 0; col < Mat->cols; col++) {
                            if (row == col) {
                                error = SetElement(Mat, row, col, 1.0f);
                            } else {
                                error = SetElement(Mat, row, col, 0.0f);
                            }
                        }
                    }
                } else {
                    // An error was encountered when checking if the matrix is square or not.
                    // Some code here.
                }
            } else {
                // The matrix is not square.
                // Some code here.
            }
        } else {
            // The matrix is not initialized.
            // Some code here.
        }
    } else {
        // The pointer is null.
        // Some code here.
    }

    return error;
}

// Add an example here.
bool IsSquare(const Matrix *const Mat, bool *error) {
    bool isSquare = false;  // Initialize the result to false.
    *error = true;          // Initialize the error to true.

    // Check if the pointer is not null.
    if (Mat != NULL) {
        // Check if the matrix is initialized.
        if (Mat->initialized) {
            // If the matrix has the same number of rows as columns, it is square.
            if (Mat->rows == Mat->cols) {
                isSquare = true;
                *error = false;
            }
        } else {
            // The matrix is not initialized.
            // Some code here.
        }
    } else {
        // The pointer is null.
        // Some code here.
    }

    return isSquare;
}

// Add an example here.
bool AreSameSize(const Matrix *const MatA, const Matrix *const MatB, bool *error) {
    bool areSameSize = false;   // Initialize the result to false.
    *error = true;              // Initialize the error to true.

    // Check if the pointer to the matrix A is not null.
    if (MatA != NULL) {
        // Check if the pointer to the matrix B is not null.
        if (MatB != NULL) {
            // Check if the matrix A is initialized.
            if (MatA->initialized) {
                // Check if the matrix B is initialized.
                if (MatB->initialized) {
                    // Check if matrix A has the same number of rows as matrix B.
                    if (MatA->rows == MatB->rows) {
                        // Check if matrix A has the same number of columns as matrix B.
                        if (MatA->cols == MatB->cols) {
                            areSameSize = true;
                            *error = false;
                        } else {
                            // The matrix A has not the same number of columns as matrix B.
                            // Some code here.
                        }
                    } else {
                        // The matrix A has not the same number of rows as matrix B.
                        // Some code here.
                    }
                } else {
                    // The matrix B is not initialized.
                    // Some code here.
                }
            } else {
                // The matrix A is not initialized.
                // Some code here.
            }
        } else {
            // The pointer to the matrix B is null.
            // Some code here.
        }
    } else {
        // The pointer to the matrix A is null.
        // Some code here.
    }

    return areSameSize;
}

// Add an example here.
bool CopyMatrix(const Matrix *const MatA, Matrix *MatB) {
    bool error = true;  // Initialize the error to true.

    // Check if the pointer to the matrix A is not null.
    if (MatA != NULL) {
        // Check if the pointer to the matrix B is not null.
        if (MatB != NULL) {
            // Check if the matrix A is initialized.
            if (MatA->initialized) {
                // Check if the matrix B is initialized.
                if (MatB->initialized) {
                    // Check if matrices A and B have the same dimensions.
                    if (AreSameSize(MatA, MatB, &error)) {
                        if (!error) {
                            // Iterate through each element and copy it from matrix A to matrix B.
                            for (uint8_t row = 0; row < MatA->rows; row++) {
                                for (uint8_t col = 0; col < MatA->cols; col++) {
                                    float element = GetElement(MatA, row, col, &error);

                                    if (!error) {
                                        error = SetElement(MatB, row, col, element);
                                    }
                                }
                            }
                        } else {
                            // An error was encountered when checking if the dimensions of the matrices A and B are the same or not.
                            // Some code here.
                        }
                    } else {
                        // The matrices A and B do not have the same dimensions.
                        // Some code here.
                    }
                } else {
                    // The matrix B is not initialized.
                    // Some code here.
                }
            } else {
                // The matrix A is not initialized.
                // Some code here.
            }
        } else {
            // The pointer to the matrix B is null.
            // Some code here.
        }
    } else {
        // The pointer to the matrix A is null.
        // Some code here.
    }

    return error;
}

bool IsEqual(const Matrix *const MatA, const Matrix *const MatB, bool *error, const float deviation) {
    bool isEqual = false;    // Initialize the result to false.

    *error = true;

    // Check if the pointer to the matrix A is not null.
    if (MatA != NULL) {
        // Check if the pointer to the matrix B is not null.
        if (MatB != NULL) {
            // Check if the matrix A is initialized.
            if (MatA->initialized) {
                // Check if the matrix B is initialized.
                if (MatB->initialized) {
                    // Check if matrix A has the same number of rows as matrix B.
                    if (MatA->rows == MatB->rows) {
                        // Iterate through each element and check if they are close within the deviation.
                        for (uint8_t row = 0; row < MatA->rows; row++) {
                            for (uint8_t col = 0; col < MatA->cols; col++) {
                                // Need a small update here.
                                isEqual = CloseAll(GetElement(MatA, row, col, error), GetElement(MatB, row, col, error), deviation);

                                if (!isEqual) {
                                    // There's no need to go on. The two matrices are different.
                                    break;
                                }
                            }

                            if (!isEqual) {
                                // There's no need to go on. The two matrices are different.
                                break;
                            }
                        }
                    } else {
                        // The matrix A has not the same number of rows as matrix B.
                        // Some code here.
                    }
                } else {
                    // The matrix B is not initialized.
                    // Some code here.
                }
            } else {
                // The matrix A is not initialized.
                // Some code here.
            }
        } else {
            // The pointer to the matrix B is null.
            // Some code here.
        }
    } else {
        // The pointer to the matrix A is null.
        // Some code here.
    }

    return isEqual; // Return the result indicating if the matrices are equal.
}

bool PrintMatrix(const Matrix *const Mat) {
    bool error = true;  // Initialize the error to true.

    // Check if the pointer is not null.
    if (Mat != NULL) {
        // Check if the matrix is initialized.
        if (Mat->initialized) {
            // Iterate through each element and print it with a tab separator.
            for (uint8_t row = 0; row < Mat->rows; row++) {
                for (uint8_t col = 0; col < Mat->cols; col++) {
                    //printf("%.3f ",  GetElement(Mat, row, col, &error));
                    printf("%.3f\t",  GetElement(Mat, row, col, &error));

                    if (error) {
                        // There's no need to go on.
                        break;
                    }
                }

                printf("\n");   // Move to the next row with a newline character.

                if (error) {
                    // There's no need to go on.
                    break;
                }
            }

            printf("\n");   // Print an additional newline for better formatting.
        } else {
            // The matrix is not initialized.
            // Some code here.
        }
    } else {
        // The pointer is null.
        // Some code here.
    }

    return error;
}

void PrintfBool(bool var) {
    if (var) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

int main() {
    /* The purpose of this code is to test the operation of the functions in the "Linalg" library. */

    #define M   3   // This value must be less than or equal to M_MAX.
    #define N   3   // This value must be less than or equal to N_MAX.

    bool error = false;

    const uint8_t rows = M;
    const uint8_t cols = N;

    Matrix Mat = InitMatrix(NULL, rows, cols);
    //Matrix Mat;   // Deliberately generate errors.
    error = PrintMatrix(&Mat);
    PrintfBool(error);
    error = FillIdentityMatrix(&Mat);
    PrintfBool(error);
    error = PrintMatrix(&Mat);
    PrintfBool(error);
    float value = 2.0f;
    error = FillMatrix(&Mat, value);
    PrintfBool(error);
    error = PrintMatrix(&Mat);
    PrintfBool(error);

    /*
    // The code below is the same as the code above.
    CreateMatrix(Mat);
    InitMatrix(&Mat, rows, cols);
    error = PrintMatrix(&Mat);
    PrintfBool(error);
    error = FillIdentityMatrix(&Mat);
    PrintfBool(error);
    error = PrintMatrix(&Mat);
    PrintfBool(error);
    float value = 2.0f;
    error = FillMatrix(&Mat, value);
    PrintfBool(error);
    error = PrintMatrix(&Mat);
    PrintfBool(error);
    */

    // Some code here.

    return error;
}
