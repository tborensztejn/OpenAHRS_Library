#include "../includes/Matrix.h"

// Add an example here.
Matrix InitMatrix(Matrix *Mat, const uint8_t rows, const uint8_t cols, bool *error, ErrorType *errorType) {
    *error = true;  // Set the error flag to true.

    // The check routine verifies that the pointer to the matrix is not null, that the matrix has not already been initialized and that there are no buffer overflow attempts.

    // Check that the pointer is not null.
    if (Mat != NULL) {
        // Check if the matrix has already been initialized.
        if (!Mat->initialized) {
            // Check that the number of rows does not exceed M_MAX (to avoid buffer overflow).
            if (IsValidRowsNumber(rows)) {
                // Check that the number of columns does not exceed N_MAX (to avoid buffer overflow).
                if (IsValidColsNumber(cols)) {
                    Mat->rows = rows;           // Set the number of rows in the new matrix.
                    Mat->cols = cols;           // Set the number of columns in the new matrix.
                    Mat->initialized = true;    // Set the initialization flag to true.

                    *error = false;             // Set the error flag to false.
                    *errorType = NO_ERROR;      // Set the error type.
                } else {
                    // The number of columns exceeds N_MAX.
                    *errorType = INVALID_COLS_NUMBER;   // Set the error type.
                }
            } else {
                // The number of rows exceeds M_MAX.
                *errorType = INVALID_ROWS_NUMBER;   // Set the error type.
            }
        } else {
            // The matrix has already been initialized.
            *errorType = ALREADY_INIT;  // Set the error type.
        }
    } else {
        // The pointer is null.
        //Matrix NewMatrix = MATRIX_INITIALIZER;
        CreateMatrix(NewMatrix);

        // Check that the number of rows does not exceed M_MAX (to avoid buffer overflow).
        if (IsValidRowsNumber(rows)) {
            // Check that the number of columns does not exceed N_MAX (to avoid buffer overflow).
            if (IsValidColsNumber(cols)) {
                NewMatrix.rows = rows;          // Set the number of rows in the new matrix.
                NewMatrix.cols = cols;          // Set the number of columns in the new matrix.
                NewMatrix.initialized = true;   // Set the initialization flag to true.

                *error = false;                 // Set the error flag to false.
                *errorType = NO_ERROR;          // Set the error type.

                return NewMatrix;   // Return the initialized new matrix.
            } else {
                // The number of columns exceeds N_MAX.
                *errorType = INVALID_COLS_NUMBER;   // Set the error type.
            }
        } else {
            // The number of rows exceeds M_MAX.
            *errorType = INVALID_ROWS_NUMBER;   // Set the error type.
        }

        //return NewMatrix;   // Return the initialized new matrix.
    }
}

// Add an example here.
bool ApplyRoutineMatrixChecks(const Matrix *const Mat, ErrorType *errorType, const uint8_t *const row, const uint8_t *const col) {
    bool error = true;  // Initialize the error flag to true.

    // The check routine verifies that the pointer to the matrix is not null, that the matrix is initialized and that there are no buffer overflow attempts.

    // Check that the pointer is not null.
    if (Mat != NULL) {
        // Check that the matrix is initialized.
        if (Mat->initialized) {
            // Check that the number of rows does not exceed M_MAX (to avoid buffer overflow).
            if (IsValidRowsNumber(Mat->rows)) {
                // Check that the number of columns does not exceed N_MAX (to avoid buffer overflow).
                if (IsValidColsNumber(Mat->cols)) {
                    if (row != NULL) {
                        // Check if the row exists.
                        if (IsValidRow(*row, Mat->rows)) {
                            // Routine checks were successfully completed.
                            // This matrix is fully operational.
                            error = false;          // Set the error flag to false.
                            *errorType = NO_ERROR;  // Set the error type.
                        } else {
                            // The row does not exist.
                            *errorType = NON_EXISTING_ROW;  // Set the error type.
                        }
                    } else {
                        // No row specified to check.
                        // Routine checks were successfully completed.
                        // This matrix is fully operational.
                        error = false;          // Set the error flag to false.
                        *errorType = NO_ERROR;  // Set the error type.
                    }

                    if (col != NULL) {
                        // Check if the column exists.
                        if (IsValidCol(*col, Mat->rows)) {
                            // Routine checks were successfully completed.
                            // This matrix is fully operational.
                            error = false;          // Set the error flag to false.
                            *errorType = NO_ERROR;  // Set the error type.
                        } else {
                            // The column does not exist.
                            *errorType = NON_EXISTING_COL;  // Set the error type.
                        }
                    } else {
                        // No column specified to check.
                        // Routine checks were successfully completed.
                        // This matrix is fully operational.
                        error = false;          // Set the error flag to false.
                        *errorType = NO_ERROR;  // Set the error type.
                    }
                } else {
                    // The number of columns exceeds N_MAX.
                    *errorType = INVALID_COLS_NUMBER;   // Set the error type.
                }
            } else {
                // The number of rows exceeds M_MAX.
                *errorType = INVALID_ROWS_NUMBER;   // Set the error type.
            }
        } else {
            // The matrix is not initialized.
            *errorType = UNINITIALIZED;   // Set the error type.
        }
    } else {
        // The pointer is null.
        *errorType = NULL_PTR;  // Set the error type.
    }

    return error;   // Return the state of the error flag.
}













/*
// Add an example here.
bool SetMatrixElement(Matrix *Mat, const uint8_t row, const uint8_t col, const float value, const bool check) {
    bool error = true;  // Initialize the error flag to true.

    // The routine checks that the pointer to the matrix is not null, that the matrix is initialized and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer to the matrix is not null.
        if (Mat != NULL) {
            // Check if the matrix is initialized.
            if (Mat->initialized) {
                // Check if the row exists (to prevent buffer overflow).
                if (IsValidRow(row)) {
                    // Check if the column exists (to prevent buffer overflow).
                    if (IsValidCol(col)) {
                        // Check if the value is valid.
                        if (!isnan(value)) {
                            Mat->elements[row * Mat->cols + col] = value;   // Set the value of the specified element in the matrix.
                            error = false;                                  // Set the error flag to false.
                        } else {
                            // The value is not valid.
                            // Some code here.
                        }
                    } else {
                        // The column does not exist.
                        // Some code here.
                    }
                } else {
                    // The row does not exist.
                    // Some code here.
                }
            } else {
                // The matrix is not initialized.
                // Some code here.
            }
        } else {
            // The pointer to the matrix is null.
            // Some code here.
        }
    } else {
        // Bypassing the routine verifications.
        // Check if the value is valid.
        if (!isnan(value)) {
            Mat->elements[row * Mat->cols + col] = value;   // Set the value of the specified element in the matrix.
            error = false;                                  // Set the error flag to false.
        } else {
            // The value is not valid.
            // Some code here.
        }
    }

    return error;   // Return the state of the error flag.
}

// Add an example here.
float GetMatrixElement(const Matrix *const Mat, const uint8_t row, const uint8_t col, bool *error, const bool check) {
    float element;  // Declare the variable that will store the returned value.
    *error = true;  // Set the error flag to true.

    // The routine checks that the pointer to the matrix is not null, that the matrix is initialized and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer to the matrix is not null.
        if (Mat != NULL) {
            // Check if the matrix is initialized.
            if (Mat->initialized) {
                // Check if the row exists (to prevent buffer overflow).
                if (IsValidRow(row)) {
                    // Check if the column exists (to prevent buffer overflow).
                    if (IsValidCol(col)) {
                        element = Mat->elements[row * Mat->cols + col];   // Retrieve the value of the specified element from the matrix.

                        // Check if the value of the element is valid.
                        if (!isnan(element)) {
                            *error = false; // Set the error flag to false.
                        } else {
                            // The value of the element is not valid.
                            // Some code here.
                        }
                    } else {
                        // The column does not exist.
                        element = NAN;
                        // Some code here.
                    }
                } else {
                    // The row does not exist.
                    element = NAN;
                    // Some code here.
                }
            } else {
                // The matrix is not initialized.
                element = NAN;
                // Some code here.
            }
        } else {
            // The pointer to the matrix is null.
            element = NAN;
            // Some code here.
        }
    } else {
        // Bypassing the routine verifications.
        element = Mat->elements[row * Mat->cols + col];   // Retrieve the value of the specified element from the matrix.

        // Check if the element is valid.
        if (!isnan(element)) {
            *error = false; // Set the error flag to false.
        } else {
            // The value of the element is not valid.
            // Some code here.
        }
    }

    return element; // Return the value of the specified element from the matrix.
}

// Add an example here.
bool FillMatrix(Matrix *Mat, const float value, const bool check) {
    bool error = true;  // Initialize the error flag to true.

    // The routine checks that the pointer to the matrix is not null, that the matrix is initialized and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer to the matrix is not null.
        if (Mat != NULL) {
            // Check if the matrix is initialized.
            if (Mat->initialized) {
                // Check if the numbers of rows of the matrix do not exceed M_MAX.
                if (IsValidRow(Mat->rows)) {
                    // Check if the numbers of columns of the matrix do not exceed N_MAX.
                    if (IsValidCol(Mat->cols)) {
                        // Assign the value to each element of the matrix.
                        for (uint8_t row = 0; row < Mat->rows; row++) {
                            for (uint8_t col = 0; col < Mat->cols; col++) {
                                // There is not need to check if the value is valid.
                                // Even if NO_ROUTINE_CHECK is used when calling SetMatrixElement(), the function still returns an error if the value is invalid.
                                error = SetMatrixElement(Mat, row, col, value, NO_ROUTINE_CHECK);

                                // Break the inner loop if there is an error.
                                if (error) {
                                    // There is no need to go on.
                                    // Some code here.
                                    break;
                                }
                            }

                            // Break the outer loop if there is an error.
                            if (error) {
                                // There is no need to go on.
                                // Some code here.
                                break;
                            }
                        }
                    } else {
                        // The number of columns of the matrix exceeds N_MAX.
                        // Some code here.
                    }
                } else {
                    // The number of rows of the matrix exceeds M_MAX.
                    // Some code here.
                }
            } else {
                // The matrix is not initialized.
                // Some code here.
            }
        } else {
            // The pointer to the matrix is null.
            // Some code here.
        }
    } else {
        // Bypassing the routine verifications.
        // Assign the value to each element of the matrix.
        for (uint8_t row = 0; row < Mat->rows; row++) {
            for (uint8_t col = 0; col < Mat->cols; col++) {
                // There is not need to check if the value is valid.
                // Even if NO_ROUTINE_CHECK is used when calling SetMatrixElement(), the function still returns an error if the value is invalid.
                error = SetMatrixElement(Mat, row, col, value, NO_ROUTINE_CHECK);

                // Break the inner loop if there is an error.
                if (error) {
                    // There is no need to go on.
                    // Some code here.
                    break;
                }
            }

            // Break the outer loop if there is an error.
            if (error) {
                // There is no need to go on.
                // Some code here.
                break;
            }
        }
    }

    return error;   // Return the state of the error flag.
}

// Add an example here.
bool FillIdentityMatrix(Matrix *Mat, const bool check) {
    bool error = true;  // Initialize the error flag to true.

    // The routine checks that the pointer to the matrix is not null, that the matrix is initialized and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer to the matrix is not null.
        if (Mat != NULL) {
            // Check if the matrix is initialized.
            if (Mat->initialized) {
                // Check if the numbers of rows of the matrix do not exceed M_MAX.
                if (IsValidRow(Mat->rows)) {
                    // Check if the numbers of columns of the matrix do not exceed N_MAX.
                    if (IsValidCol(Mat->cols)) {
                        // Check if the matrix is square.
                        if (IsSquare(Mat, &error, NO_ROUTINE_CHECK)) {
                            if (!error) {
                                // Set the diagonal elements to one.
                                for (uint8_t row = 0; row < Mat->rows; row++) {
                                    for (uint8_t col = 0; col < Mat->cols; col++) {
                                        if (row == col) {
                                            error = SetMatrixElement(Mat, row, col, 1.0f, NO_ROUTINE_CHECK);
                                        } else {
                                            error = SetMatrixElement(Mat, row, col, 0.0f, NO_ROUTINE_CHECK);
                                        }

                                        // Break the inner loop if there is an error.
                                        if (error) {
                                            // There is no need to go on.
                                            // Some code here.
                                            break;
                                        }
                                    }

                                    // Break the outer loop if there is an error.
                                    if (error) {
                                        // There is no need to go on.
                                        // Some code here.
                                        break;
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
                        // The number of columns of the matrix exceeds N_MAX.
                        // Some code here.
                    }
                } else {
                    // The number of rows of the matrix exceeds M_MAX.
                    // Some code here.
                }
            } else {
                // The matrix is not initialized.
                // Some code here.
            }
        } else {
            // The pointer to the matrix is null.
            // Some code here.
        }
    } else {
        // Bypassing the routine verifications.
        // Check if the matrix is square.
        if (IsSquare(Mat, &error, NO_ROUTINE_CHECK)) {
            if (!error) {
                // Set the diagonal elements to one.
                for (uint8_t row = 0; row < Mat->rows; row++) {
                    for (uint8_t col = 0; col < Mat->cols; col++) {
                        if (row == col) {
                            error = SetMatrixElement(Mat, row, col, 1.0f, NO_ROUTINE_CHECK);
                        } else {
                            error = SetMatrixElement(Mat, row, col, 0.0f, NO_ROUTINE_CHECK);
                        }

                        // Break the inner loop if there is an error.
                        if (error) {
                            // There is no need to go on.
                            // Some code here.
                            break;
                        }
                    }

                    // Break the outer loop if there is an error.
                    if (error) {
                        // There is no need to go on.
                        // Some code here.
                        break;
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
    }

    return error;   // Return the state of the error flag.
}

// Add an example here.
bool CopyMatrix(const Matrix *const MatA, Matrix *MatB, const bool check) {
    bool error = true;  // Initialize the error to true.

    // The routine checks that the pointers to the matrices are not null, that the matrices are initialized and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer to the matrix A is not null.
        if (MatA != NULL) {
            // Check if the pointer to the matrix B is not null.
            if (MatB != NULL) {
                // Check if the matrix A is initialized.
                if (MatA->initialized) {
                    // Check if the matrix B is initialized.
                    if (MatB->initialized) {
                        // Check if the numbers of rows of the matrix A do not exceed M_MAX.
                        if (IsValidRow(MatA->rows)) {
                            // Check if the numbers of rows of the matrix B do not exceed M_MAX.
                            if (IsValidRow(MatB->rows)) {
                                // Check if the numbers of columns of the matrix A do not exceed N_MAX.
                                if (IsValidCol(MatA->cols)) {
                                    // Check if the numbers of columns of the matrix B do not exceed N_MAX.
                                    if (IsValidCol(MatB->cols)) {
                                        // Check if the matrices A and B have the same dimensions.
                                        if (AreSameSizeM(MatA, MatB, &error, NO_ROUTINE_CHECK)) {
                                            if (!error) {
                                                // Iterate through each element and copy it from matrix A to matrix B.
                                                for (uint8_t row = 0; row < MatA->rows; row++) {
                                                    for (uint8_t col = 0; col < MatA->cols; col++) {
                                                        // There is not need to check if the value is valid.
                                                        // Even if NO_ROUTINE_CHECK is used when calling GetMatrixElement(), the function still returns an error if the value is invalid.
                                                        float element = GetMatrixElement(MatA, row, col, &error, NO_ROUTINE_CHECK);

                                                        // If no errors are encountered when retrieving the value of the element.
                                                        if (!error) {
                                                            // There is not need to check if the value is valid.
                                                            // Even if NO_ROUTINE_CHECK is used when calling SetMatrixElement(), the function still returns an error if the value is invalid.
                                                            error = SetMatrixElement(MatB, row, col, element, NO_ROUTINE_CHECK);

                                                            if (error) {
                                                                // There is not need to go on.
                                                                // Some code here.
                                                                break;
                                                            }
                                                        } else {
                                                            // There is not need to go on.
                                                            // Some code here.
                                                            break;
                                                        }
                                                    }

                                                    if (error) {
                                                        // There is not need to go on.
                                                        // Some code here.
                                                        break;
                                                    }
                                                }
                                            } else {
                                                // An error was encountered when checking the similarity of the dimensions of the matrices A and B.
                                                // Some code here.
                                            }
                                        } else {
                                            // The matrices A and B do not have the same dimensions.
                                            // Some code here.
                                        }
                                    } else {
                                        // The number of columns of the matrix B exceeds N_MAX.
                                        // Some code here.
                                    }
                                } else {
                                    // The number of columns of the matrix A exceeds N_MAX.
                                    // Some code here.
                                }
                            } else {
                                // The number of rows of the matrix B exceeds M_MAX.
                                // Some code here.
                            }
                        } else {
                            // The number of rows of the matrix A exceeds M_MAX.
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
    } else {
        // Bypassing the routine verifications.
        // Check if the matrices A and B have the same dimensions.
        if (AreSameSizeM(MatA, MatB, &error, NO_ROUTINE_CHECK)) {
            if (!error) {
                // Iterate through each element and copy it from matrix A to matrix B.
                for (uint8_t row = 0; row < MatA->rows; row++) {
                    for (uint8_t col = 0; col < MatA->cols; col++) {
                        // There is not need to check if the value is valid.
                        // Even if NO_ROUTINE_CHECK is used when calling GetMatrixElement(), the function still returns an error if the value is invalid.
                        float element = GetMatrixElement(MatA, row, col, &error, NO_ROUTINE_CHECK);

                        // If no errors are encountered when retrieving the value of the element.
                        if (!error) {
                            // There is not need to check if the value is valid.
                            // Even if NO_ROUTINE_CHECK is used when calling SetMatrixElement(), the function still returns an error if the value is invalid.
                            error = SetMatrixElement(MatB, row, col, element, NO_ROUTINE_CHECK);

                            if (error) {
                                // There is not need to go on.
                                // Some code here.
                                break;
                            }
                        } else {
                            // There is not need to go on.
                            // Some code here.
                            break;
                        }
                    }
                    if (error) {
                        // There is not need to go on.
                        // Some code here.
                        break;
                    }
                }
            } else {
                // An error was encountered when checking the similarity of the dimensions of the matrices A and B.
                // Some code here.
            }
        } else {
            // The matrices A and B do not have the same dimensions.
            // Some code here.
        }
    }

    return error;   // Return the state of the error flag.
}

// Add an example here.
bool AreEqualM(const Matrix *const MatA, const Matrix *const MatB, const float deviation, bool *error, const bool check) {
    bool areEqual = false;  // Initialize the result to false.
    *error = true;          // Set the error flag to true.

    // The routine checks that the pointers to the matrices are not null, that the matrices are initialized and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer to the matrix A is not null.
        if (MatA != NULL) {
            // Check if the pointer to the matrix B is not null.
            if (MatB != NULL) {
                // Check if the matrix A is initialized.
                if (MatA->initialized) {
                    // Check if the matrix B is initialized.
                    if (MatB->initialized) {
                        // Check if the numbers of rows of the matrix A do not exceed M_MAX.
                        if (IsValidRow(MatA->rows)) {
                            // Check if the numbers of rows of the matrix B do not exceed M_MAX.
                            if (IsValidRow(MatB->rows)) {
                                // Check if the numbers of columns of the matrix A do not exceed N_MAX.
                                if (IsValidCol(MatA->cols)) {
                                    // Check if the numbers of columns of the matrix B do not exceed N_MAX.
                                    if (IsValidCol(MatB->cols)) {
                                        // Check if the matrices A and B have the same dimensions.
                                        if (AreSameSizeM(MatA, MatB, error, NO_ROUTINE_CHECK)) {
                                            if (!error) {
                                                // Iterate through each element and check if they are close within the deviation.
                                                for (uint8_t row = 0; row < MatA->rows; row++) {
                                                    for (uint8_t col = 0; col < MatA->cols; col++) {
                                                        // Retrieve the value of the specified element from the matrix A.
                                                        float elementA = GetMatrixElement(MatA, row, col, error, NO_ROUTINE_CHECK);

                                                        // Check if the value of the element of the matrix A is valid.
                                                        // Even if NO_ROUTINE_CHECK is used when calling GetMatrixElement(), the function still returns an error if the value is invalid.
                                                        if (!error) {
                                                            // Retrieve the value of the specified element from the matrix B.
                                                            float elementB = GetMatrixElement(MatB, row, col, error, NO_ROUTINE_CHECK);

                                                            // Check if the value of the element of the matrix B is valid.
                                                            // Even if NO_ROUTINE_CHECK is used when calling GetMatrixElement(), the function still returns an error if the value is invalid.
                                                            if (!error) {
                                                                areEqual = CloseAll(elementA, elementB, deviation);

                                                                if (!areEqual) {
                                                                    // The two matrices are different.
                                                                    // There is no need to go on.
                                                                    // Some code here.
                                                                    break;
                                                                }
                                                            } else {
                                                                // The value of the element of the matrix B is not valid.
                                                                // There is no need to go on.
                                                                // Some code here.
                                                                break;
                                                            }
                                                        } else {
                                                            // The value of the element of the matrix A is not valid.
                                                            // There is no need to go on.
                                                            // Some code here.
                                                            break;
                                                        }
                                                    }

                                                    if (!areEqual) {
                                                        // The two matrices are different.
                                                        // There is no need to go on.
                                                        // Some code here.
                                                        break;
                                                    }

                                                    if (error) {
                                                        // There is no need to go on.
                                                        // Some code here.
                                                        break;
                                                    }
                                                }
                                            } else {
                                                // An error was encountered when checking the similarity of the dimensions of matrices A and B.
                                                // Some code here.
                                            }
                                        } else {
                                            // The matrices A and B do not have the same dimensions.
                                            // Some code here.
                                        }
                                    } else {
                                        // The number of columns of the matrix B exceeds N_MAX.
                                        // Some code here.
                                    }
                                } else {
                                    // The number of columns of the matrix A exceeds N_MAX.
                                    // Some code here.
                                }
                            } else {
                                // The number of rows of the matrix B exceeds M_MAX.
                                // Some code here.
                            }
                        } else {
                            // The number of rows of the matrix A exceeds M_MAX.
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
    } else {
        // Bypassing the routine verifications.
        // Check if the matrices A and B have the same dimensions.
        if (AreSameSizeM(MatA, MatB, error, NO_ROUTINE_CHECK)) {
            if (!error) {
                // Iterate through each element and check if they are close within the deviation.
                for (uint8_t row = 0; row < MatA->rows; row++) {
                    for (uint8_t col = 0; col < MatA->cols; col++) {
                        // Retrieve the value of the specified element from the matrix A.
                        float elementA = GetMatrixElement(MatA, row, col, error, NO_ROUTINE_CHECK);

                        // Check if the value of the element of the matrix A is valid.
                        // Even if NO_ROUTINE_CHECK is used when calling GetMatrixElement(), the function still returns an error if the value is invalid.
                        if (!error) {
                            // Retrieve the value of the specified element from the matrix B.
                            float elementB = GetMatrixElement(MatB, row, col, error, NO_ROUTINE_CHECK);

                            // Check if the value of the element of the matrix B is valid.
                            // Even if NO_ROUTINE_CHECK is used when calling GetMatrixElement(), the function still returns an error if the value is invalid.
                            if (!error) {
                                areEqual = CloseAll(elementA, elementB, deviation);

                                if (!areEqual) {
                                    // The two matrices are different.
                                    // There is no need to go on.
                                    // Some code here.
                                    break;
                                }
                            } else {
                                // The value of the element of the matrix B is not valid.
                                // There is no need to go on.
                                // Some code here.
                                break;
                            }
                        } else {
                            // The value of the element of the matrix A is not valid.
                            // There is no need to go on.
                            // Some code here.
                            break;
                        }
                    }

                    if (!areEqual) {
                        // The two matrices are different.
                        // There is no need to go on.
                        // Some code here.
                        break;
                    }

                    if (error) {
                        // There is no need to go on.
                        // Some code here.
                        break;
                    }
                }
            } else {
                // An error was encountered when checking the similarity of the dimensions of matrices A and B.
                // Some code here.
            }
        } else {
            // The matrices A and B do not have the same dimensions.
            // Some code here.
        }
    }

    return areEqual;    // Return the result.
}

// Add an example here.
bool IsSquare(const Matrix *const Mat, bool *error, const bool check) {
    bool isSquare = false;  // Initialize the result to false.
    *error = true;          // Set the error flag to true.

    // The routine checks that the pointer to the matrix is not null, that the matrix is initialized and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer is not null.
        if (Mat != NULL) {
            // Check if the matrix is initialized.
            if (Mat->initialized) {
                // Check if the numbers of rows of the matrix do not exceed M_MAX.
                if (IsValidRow(Mat->rows)) {
                    // Check if the numbers of columns of the matrix do not exceed N_MAX.
                    if (IsValidCol(Mat->cols)) {
                        // If the matrix has the same number of rows as columns, it is square.
                        if (Mat->rows == Mat->cols) {
                            isSquare = true;    // Set the result to true.
                            *error = false;     // Set the error flag to false.
                        } else {
                            // The matrix is not square.
                            // Some code here.
                        }
                    } else {
                        // The number of columns of the matrix exceeds N_MAX.
                        // Some code here.
                    }
                } else {
                    // The number of rows of the matrix exceeds M_MAX.
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
    } else {
        // Bypassing the routine verifications.
        // If the matrix has the same number of rows as columns, it is square.
        if (Mat->rows == Mat->cols) {
            isSquare = true;    // Set the result to true.
            *error = false;     // Set the error flag to false.
        } else {
            // The matrix is not square.
            // Some code here.
        }
    }

    return isSquare;    // Return the result.
}

// Add an example here.
bool AreSameSizeM(const Matrix *const MatA, const Matrix *const MatB, bool *error, const bool check) {
    bool areSameSize = false;   // Initialize the result to false.
    *error = true;              // Set the error flag to true.

    // The routine checks that the pointer to the matrix is not null, that the matrix is initialized and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer to the matrix A is not null.
        if (MatA != NULL) {
            // Check if the pointer to the matrix B is not null.
            if (MatB != NULL) {
                // Check if the matrix A is initialized.
                if (MatA->initialized) {
                    // Check if the matrix B is initialized.
                    if (MatB->initialized) {
                        // Check if the numbers of rows of the matrix A do not exceed M_MAX.
                        if (IsValidRow(MatA->rows)) {
                            // Check if the numbers of rows of the matrix B do not exceed M_MAX.
                            if (IsValidRow(MatB->rows)) {
                                // Check if the numbers of columns of the matrix A do not exceed N_MAX.
                                if (IsValidCol(MatA->cols)) {
                                    // Check if the numbers of columns of the matrix B do not exceed N_MAX.
                                    if (IsValidCol(MatB->cols)) {
                                        // Check if matrix A has the same number of rows as matrix B.
                                        if (MatA->rows == MatB->rows) {
                                            // Check if matrix A has the same number of columns as matrix B.
                                            if (MatA->cols == MatB->cols) {
                                                areSameSize = true; // Set the result to true.
                                                *error = false;     // Set the error flag to false.
                                            } else {
                                                // The matrix A has not the same number of columns as matrix B.
                                                // Some code here.
                                            }
                                        } else {
                                            // The matrix A has not the same number of rows as matrix B.
                                            // Some code here.
                                        }
                                    } else {
                                        // The number of columns of the matrix B exceeds N_MAX.
                                        // Some code here.
                                    }
                                } else {
                                    // The number of columns of the matrix A exceeds N_MAX.
                                    // Some code here.
                                }
                            } else {
                                // The number of rows of the matrix B exceeds M_MAX.
                                // Some code here.
                            }
                        } else {
                            // The number of rows of the matrix A exceeds M_MAX.
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
    } else {
        // Bypassing the routine verifications.
        // Check if matrix A has the same number of rows as matrix B.
        if (MatA->rows == MatB->rows) {
            // Check if matrix A has the same number of columns as matrix B.
            if (MatA->cols == MatB->cols) {
                areSameSize = true; // Set the result to true.
                *error = false;     // Set the error flag to false.
            } else {
                // The matrix A has not the same number of columns as matrix B.
                // Some code here.
            }
        } else {
            // The matrix A has not the same number of rows as matrix B.
            // Some code here.
        }
    }
    return areSameSize; // Return the result.
}

// Add an example here.
bool PrintMatrix(const Matrix *const Mat, const bool check) {
    bool error = true;  // Initialize the error flag to true.

    // The routine checks that the pointer to the matrix is not null, that the matrix is initialized and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer is not null.
        if (Mat != NULL) {
            // Check if the matrix is initialized.
            if (Mat->initialized) {
                // Check if the numbers of rows of the matrix do not exceed M_MAX.
                if (IsValidRow(Mat->rows)) {
                    // Check if the numbers of columns of the matrix do not exceed N_MAX.
                    if (IsValidCol(Mat->cols)) {
                        // Iterate through each element and print it with a tab separator.
                        for (uint8_t row = 0; row < Mat->rows; row++) {
                            for (uint8_t col = 0; col < Mat->cols; col++) {
                                //printf("%.3f ",  GetMatrixElement(Mat, row, col, &error, NO_ROUTINE_CHECK));
                                printf("%.3f\t",  GetMatrixElement(Mat, row, col, &error, NO_ROUTINE_CHECK));

                                if (error) {
                                    // There is no need to go on.
                                    break;
                                }
                            }

                            printf("\n");   // Move to the next row with a newline character.

                            if (error) {
                                // There is no need to go on.
                                break;
                            }
                        }

                        printf("\n");   // Print an additional newline for better formatting.
                    } else {
                        // The number of columns of the matrix exceeds N_MAX.
                        // Some code here.
                    }
                } else {
                    // The number of rows of the matrix exceeds M_MAX.
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
    } else {
        // Bypassing the routine verifications.
        // Iterate through each element and print it with a tab separator.
        for (uint8_t row = 0; row < Mat->rows; row++) {
            for (uint8_t col = 0; col < Mat->cols; col++) {
                //printf("%.3f ",  GetMatrixElement(Mat, row, col, &error, NO_ROUTINE_CHECK));
                printf("%.3f\t",  GetMatrixElement(Mat, row, col, &error, NO_ROUTINE_CHECK));

                if (error) {
                    // There is no need to go on.
                    break;
                }
            }

            printf("\n");   // Move to the next row with a newline character.

            if (error) {
                // There is no need to go on.
                break;
            }
        }

        printf("\n");   // Print an additional newline for better formatting.
    }

    return error;   // Return the state of the error flag.
}

// Add an example here.
bool Add(const Matrix *const MatA, const Matrix *const MatB, Matrix *MatC) {

}
*/
