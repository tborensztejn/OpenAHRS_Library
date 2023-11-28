#include "../includes/Vector.h"

// Add an example here.
Vector InitVector(Vector *Vect, const uint8_t rows, bool *error, ErrorType *errorType) {
    *error = true;  // Set the error flag to true.

    // The check routine verifies that the pointer to the vector is not null, that the vector has not already been initialized and that there are no buffer overflow attempts.

    // Check that the pointer is not null.
    if (Vect != NULL) {
        // Check if the vector has already been initialized.
        if (!Vect->initialized) {
            // Check that the number of rows does not exceed M_MAX (to avoid buffer overflow).
            if (IsValidRowsNumber(rows)) {
                Vect->rows = rows;          // Set the number of rows in the new vector.
                Vect->initialized = true;   // Set the initialization flag to true.

                *error = false;             // Set the error flag to false.
                *errorType = NO_ERROR;      // Set the error type.
            } else {
                // The number of rows exceeds M_MAX.
                *errorType = INVALID_ROWS_NUMBER;   // Set the error type.
            }
        } else {
            // The vector has already been initialized.
            *errorType = ALREADY_INIT;  // Set the error type.
        }
    } else {
        // The pointer is null.
        //Vector NewVector = VECTOR_INITIALIZER;
        CreateVector(NewVector);

        // Check that the number of rows does not exceed M_MAX (to avoid buffer overflow).
        if (IsValidRowsNumber(rows)) {
            NewVector.rows = rows;          // Set the number of rows in the new vector.
            NewVector.initialized = true;   // Set the initialization flag to true.

            *error = false;                 // Set the error flag to false.
            *errorType = NO_ERROR;          // Set the error type.

            return NewVector;               // Return the initialized new vector.
        } else {
            // The number of rows exceeds M_MAX.
            *errorType = INVALID_ROWS_NUMBER;   // Set the error type.
        }

        //return NewVector;   // Return the initialized new vector.
    }
}

// Add an example here.
bool ApplyRoutineVectorChecks(const Vector *const Vect, ErrorType *errorType, const uint8_t *const row) {
    bool error = true;  // Initialize the error flag to true.

    // The check routine verifies that the pointer to the vector is not null, that the vector is initialized and that there are no buffer overflow attempts.

    // Check that the pointer is not null.
    if (Vect != NULL) {
        // Check that the vector is initialized.
        if (Vect->initialized) {
            // Check that the number of rows does not exceed M_MAX (to avoid buffer overflow).
            if (IsValidRowsNumber(Vect->rows)) {
                if (row != NULL) {
                    // Check if the row exists.
                    if (IsValidRow(*row, Vect->rows)) {
                        // Routine checks were successfully completed.
                        // This vector is fully operational.
                        error = false;          // Set the error flag to false.
                        *errorType = NO_ERROR;  // Set the error type.
                    } else {
                        // The row does not exist.
                        *errorType = NON_EXISTING_ROW;  // Set the error type.
                    }
                } else {
                    // No row specified to check.
                    // Routine checks were successfully completed.
                    // This vector is fully operational.
                    error = false;          // Set the error flag to false.
                    *errorType = NO_ERROR;  // Set the error type.
                }
            } else {
                // The number of rows exceeds M_MAX.
                *errorType = INVALID_ROWS_NUMBER;   // Set the error type.
            }
        } else {
            // The vector is not initialized.
            *errorType = UNINITIALIZED;   // Set the error type.
        }
    } else {
        // The pointer is null.
        *errorType = NULL_PTR;  // Set the error type.
    }

    return error;   // Return the state of the error flag.
}

// Add an example here.
bool SetVectorElement(Vector *Vect, const uint8_t row, const float value, ErrorType *errorType, const bool check) {
    bool error = true;  // Initialize the error flag to true.

    // If routine checks are required.
    if (check) {
        // Perform routine checks on the vector.
        error = ApplyRoutineVectorChecks(Vect, errorType, &row);

        if (!error) {
            // Check if the value is valid.
            if (!isnan(value)) {
                Vect->elements[row] = value;    // Set the value to the specified vector element.
                *errorType = NO_ERROR;          // Set the error type.
            } else {
                // The value is not valid.
                error = true;                   // Set the error flag to true.
                *errorType = INVALID_VALUE;     // Set the error type.
            }
        } else {
            // Critical error.
            // An error has occurred during the routine checking of the vector.
            // Add Add some code here.
        }
    } else {
        // Bypass routine checks.
        // Check if the value is valid.
        if (!isnan(value)) {
            Vect->elements[row] = value;    // Set the value to the specified vector element.
            error = false;                  // Set the error flag to false.
            *errorType = NO_ERROR;          // Set the error type.
        } else {
            // The value is not valid.
            *errorType = INVALID_VALUE;  // Set the error type.
        }
    }

    return error;   // Return the state of the error flag.
}

// Add an example here.
float GetVectorElement(const Vector *const Vect, const uint8_t row, bool *error, ErrorType *errorType, const bool check) {
    float element;  // Declare the variable that will store the returned value.
    *error = true;  // Set the error flag to true.

    // If routine checks are required.
    if (check) {
        // Perform routine checks on the vector.
        *error = ApplyRoutineVectorChecks(Vect, errorType, &row);

        if (!*error) {
            element = Vect->elements[row];  // Retrieve the value of the specified element from the vector.

            // Check if the value of the element is valid.
            if (!isnan(element)) {
                *errorType = NO_ERROR;  // Set the error type.
            } else {
                // The value of the element is not valid.
                *error = true;                  // Set the error flag to true.
                *errorType = INVALID_ELEMENT;   // Set the error type.
            }
        } else {
            // Critical error.
            // An error has occurred during the routine checking of the vector.
            element = NAN;
        }
    } else {
        // Bypass routine checks.
        element = Vect->elements[row];  // Retrieve the value of the specified element from the vector.

        // Check if the value of the element is valid.
        if (!isnan(element)) {
            *error = false;         // Set the error flag to false.
            *errorType = NO_ERROR;  // Set the error type.
        } else {
            // The value of the element is not valid.
            *errorType = INVALID_ELEMENT;   // Set the error type.
        }
    }

    return element; // Return the value of the specified element from the vector.
}

// Add an example here.
bool FillVector(Vector *Vect, const float value, ErrorType *errorType, const bool check) {
    bool error = true;      // Initialize the error flag to true.
    *errorType = NO_ERROR;  // Set the error type.

    // If routine checks are required.
    if (check) {
        // Perform routine checks on the vector.
        error = ApplyRoutineVectorChecks(Vect, errorType, NULL);

        if (!error) {
            // Assign the value to each element of the vector.
            for (uint8_t row = 0; row < Vect->rows; row++) {
                // There is not need to check if the value is valid.
                // Even if NO_ROUTINE_CHECK is used when calling SetVectorElement(), the function still returns an error if the value is invalid.
                error = SetVectorElement(Vect, row, value, errorType, NO_ROUTINE_CHECK);

                // Break the loop if there is an error.
                if (error) {
                    // Critical error.
                    // There is no need to go on.
                    break;
                }
            }
        } else {
            // Critical error.
            // An error has occurred during the routine checking of the vector.
            // Add Add some code here.
        }
    } else {
        // Bypass routine checks.
        // Assign the value to each element of the vector.
        for (uint8_t row = 0; row < Vect->rows; row++) {
            // There is not need to check if the value is valid.
            // Even if NO_ROUTINE_CHECK is used when calling SetVectorElement(), the function still returns an error if the value is invalid.
            error = SetVectorElement(Vect, row, value, errorType, NO_ROUTINE_CHECK);

            // Break the loop if there is an error.
            if (error) {
                // Critical error.
                // There is no need to go on.
                break;
            }
        }
    }

    return error;   // Return the state of the error flag.
}

// Add an example here.
bool CopyVector(const Vector *const VectA, Vector *VectB, ErrorType *errorType, const bool check) {
    bool error = true;      // Initialize the error flag to true.
    *errorType = NO_ERROR;  // Set the error type.

    // If routine checks are required.
    if (check) {
        // Perform routine checks on the vector A.
        error = ApplyRoutineVectorChecks(VectA, errorType, NULL);

        if (!error) {
            // Perform routine checks on the vector B.
            error = ApplyRoutineVectorChecks(VectB, errorType, NULL);

            if (!error) {
                // Check that vectors A and B have the same dimensions.
                if (AreSameSizeV(VectA, VectB, &error, errorType, NO_ROUTINE_CHECK)) {
                    if (!error) {
                        // Iterate through each element and copy it from the vector A to the vector B.
                        for (uint8_t row = 0; row < VectA->rows; row++) {
                            // There is not need to check if the value is valid.
                            // Even if NO_ROUTINE_CHECK is used when calling GetVectorElement(), the function still returns an error if the value is invalid.
                            float element = GetVectorElement(VectA, row, &error, errorType, NO_ROUTINE_CHECK);

                            // If no errors are encountered when retrieving the value of the element.
                            if (!error) {
                                // There is not need to check if the value is valid.
                                // Even if NO_ROUTINE_CHECK is used when calling SetVectorElement(), the function still returns an error if the value is invalid.
                                error = SetVectorElement(VectB, row, element, errorType, NO_ROUTINE_CHECK);

                                if (error) {
                                    // Critical error.
                                    // There is no need to go on.
                                    break;
                                }
                            } else {
                                // Critical error.
                                // There is no need to go on.
                                break;
                            }
                        }
                    } else {
                        // Critical error.
                        // An error was encountered when checking the similarity of the dimensions of vectors A and B.
                        // Add some code here.
                    }
                } else {
                    // Critical error.
                    // The vectors A and B do not have the same dimensions.
                    *errorType = SIZE_MISMATCH; // Set the error type.
                }
            } else {
                // Critical error.
                // An error has occurred during the routine checking of the vector B.
                // Add Add some code here.
            }
        } else {
            // Critical error.
            // An error has occurred during the routine checking of the vector A.
            // Add Add some code here.
        }
    } else {
        // Bypass routine checks.
        // Check that vectors A and B have the same dimensions.
        if (AreSameSizeV(VectA, VectB, &error, errorType, NO_ROUTINE_CHECK)) {
            if (!error) {
                // Iterate through each element and copy it from the vector A to the vector B.
                for (uint8_t row = 0; row < VectA->rows; row++) {
                    // There is not need to check if the value is valid.
                    // Even if NO_ROUTINE_CHECK is used when calling GetVectorElement(), the function still returns an error if the value is invalid.
                    float element = GetVectorElement(VectA, row, &error, errorType, NO_ROUTINE_CHECK);

                    // If no errors are encountered when retrieving the value of the element.
                    if (!error) {
                        // There is not need to check if the value is valid.
                        // Even if NO_ROUTINE_CHECK is used when calling SetVectorElement(), the function still returns an error if the value is invalid.
                        error = SetVectorElement(VectB, row, element, errorType, NO_ROUTINE_CHECK);

                        if (error) {
                            // Critical error.
                            // There is no need to go on.
                            break;
                        }
                    } else {
                        // Critical error.
                        // There is no need to go on.
                        break;
                    }
                }
            } else {
                // Critical error.
                // An error was encountered when checking the similarity of the dimensions of vectors A and B.
                // Add some code here.
            }
        } else {
            // Critical error.
            // The vectors A and B do not have the same dimensions.
            *errorType = SIZE_MISMATCH; // Set the error type.
        }
    }

    return error;   // Return the state of the error flag.
}

// Add an example here.
bool AreEqualV(const Vector *const VectA, const Vector *const VectB, const float deviation, bool *error, ErrorType *errorType, const bool check) {
    bool areEqual = false;  // Initialize the result to false.
    *error = true;          // Set the error flag to true.
    *errorType = NO_ERROR;  // Set the error type.

    // If routine checks are required.
    if (check) {
        // Perform routine checks on the vector A.
        *error = ApplyRoutineVectorChecks(VectA, errorType, NULL);

        if (!*error) {
            // Perform routine checks on the vector B.
            *error = ApplyRoutineVectorChecks(VectB, errorType, NULL);

            if (!*error) {
                // Check that vectors A and B have the same dimensions.
                if (AreSameSizeV(VectA, VectB, error, errorType, NO_ROUTINE_CHECK)) {
                    if (!*error) {
                        // Iterate through each element and check if they are close within the deviation.
                        for (uint8_t row = 0; row < VectA->rows; row++) {
                            // Retrieve the value of the specified element from the vector A.
                            float elementA = GetVectorElement(VectA, row, error, errorType, NO_ROUTINE_CHECK);

                            // Check if the value of the element of the vector A is valid.
                            // Even if NO_ROUTINE_CHECK is used when calling GetVectorElement(), the function still returns an error if the value is invalid.
                            if (!*error) {
                                // Retrieve the value of the specified element from the vector B.
                                float elementB = GetVectorElement(VectB, row, error, errorType, NO_ROUTINE_CHECK);

                                // Check if the value of the element of the vector B is valid.
                                // Even if NO_ROUTINE_CHECK is used when calling GetVectorElement(), the function still returns an error if the value is invalid.
                                if (!*error) {
                                    areEqual = CloseAll(elementA, elementB, deviation);

                                    if (!areEqual) {
                                        // The vectors A and B are different.
                                        // There is no need to go on.
                                        break;
                                    }
                                } else {
                                    // Critical error.
                                    // The value of the element of the vector B is not valid.
                                    // There is no need to go on.
                                    break;
                                }
                            } else {
                                // Critical error.
                                // The value of the element of the vector A is not valid.
                                // There is no need to go on.
                                break;
                            }
                        }
                    } else {
                        // Critical error.
                        // An error was encountered when checking the similarity of the dimensions of vectors A and B.
                        // Add some code here.
                    }
                } else {
                    // The vectors A and B do not have the same dimensions., so they are different.
                    // Add some code here.
                }
            } else {
                // Critical error.
                // An error has occurred during the routine checking of the vector B.
                // Add Add some code here.
            }
        } else {
            // Critical error.
            // An error has occurred during the routine checking of the vector A.
            // Add Add some code here.
        }
    } else {
        // Bypass routine checks.
        if (AreSameSizeV(VectA, VectB, error, errorType, NO_ROUTINE_CHECK)) {
            if (!*error) {
                // Iterate through each element and check if they are close within the deviation.
                for (uint8_t row = 0; row < VectA->rows; row++) {
                    // Retrieve the value of the specified element from the vector A.
                    float elementA = GetVectorElement(VectA, row, error, errorType, NO_ROUTINE_CHECK);

                    // Check if the value of the element of the vector A is valid.
                    // Even if NO_ROUTINE_CHECK is used when calling GetVectorElement(), the function still returns an error if the value is invalid.
                    if (!*error) {
                        // Retrieve the value of the specified element from the vector B.
                        float elementB = GetVectorElement(VectB, row, error, errorType, NO_ROUTINE_CHECK);

                        // Check if the value of the element of the vector B is valid.
                        // Even if NO_ROUTINE_CHECK is used when calling GetVectorElement(), the function still returns an error if the value is invalid.
                        if (!*error) {
                            areEqual = CloseAll(elementA, elementB, deviation);

                            if (!areEqual) {
                                // The vectors A and B are different.
                                // There is no need to go on.
                                break;
                            }
                        } else {
                            // Critical error.
                            // The value of the element of the vector B is not valid.
                            // There is no need to go on.
                            break;
                        }
                    } else {
                        // Critical error.
                        // The value of the element of the vector A is not valid.
                        // There is no need to go on.
                        break;
                    }
                }
            } else {
                // Critical error.
                // An error was encountered when checking the similarity of the dimensions of vectors A and B.
                // Add some code here.
            }
        } else {
            // The vectors A and B do not have the same dimensions., so they are different.
            // Add some code here.
        }
    }

    return areEqual;   // Return the result.
}

// Add an example here.
bool AreSameSizeV(const Vector *const VectA, const Vector *const VectB, bool *error, ErrorType *errorType, const bool check) {
    bool areSameSize = false;   // Initialize the result to false.
    *error = true;              // Set the error flag to true.
    *errorType = NO_ERROR;  // Set the error type.

    // If routine checks are required.
    if (check) {
        // Perform routine checks on the vector A.
        *error = ApplyRoutineVectorChecks(VectA, errorType, NULL);

        if (!*error) {
            // Perform routine checks on the vector B.
            *error = ApplyRoutineVectorChecks(VectB, errorType, NULL);

            if (!*error) {
                // Check if vector A has the same number of rows as vector B.
                if (VectA->rows == VectB->rows) {
                    areSameSize = true;
                    *error = false;
                } else {
                    // The vector A has not the same number of rows as vector B.
                    // Some code here.
                }
            } else {
                // Critical error.
                // An error has occurred during the routine checking of the vector B.
                // Add Add some code here.
            }
        } else {
            // Critical error.
            // An error has occurred during the routine checking of the vector A.
            // Add Add some code here.
        }
    } else {
        // Bypass routine checks.
        // Check if vector A has the same number of rows as vector B.
        if (VectA->rows == VectB->rows) {
            areSameSize = true;
            *error = false;
        } else {
            // The vector A has not the same number of rows as vector B.
            // Some code here.
        }
    }

    return areSameSize;   // Return the result.
}

// Add an example here.
bool PrintVector(const Vector *const Vect, ErrorType *errorType, const bool check) {
    bool error = true;      // Initialize the error flag to true.
    *errorType = NO_ERROR;  // Set the error type.

    // If routine checks are required.
    if (check) {
        // Perform routine checks on the vector.
        error = ApplyRoutineVectorChecks(Vect, errorType, NULL);

        if (!error) {
            // Iterate through each element and print it and move to the next row with a newline character.
            for (uint8_t row = 0; row < Vect->rows; row++) {
                //printf("%.5f\n",  GetVectorElement(Vect, row, &error, errorType, NO_ROUTINE_CHECK));
                printf("%.3f\n",  GetVectorElement(Vect, row, &error, errorType, NO_ROUTINE_CHECK));

                if (error) {
                    // There is no need to go on.
                    break;
                }
            }

            printf("\n");   // Print an additional newline for better formatting.
        } else {
            // Critical error.
            // An error has occurred during the routine checking of the vector.
            // Add Add some code here.
        }
    } else {
        // Bypass routine checks.
        // Iterate through each element and print it and move to the next row with a newline character.
        for (uint8_t row = 0; row < Vect->rows; row++) {
            //printf("%.5f\n",  GetVectorElement(Vect, row, &error, errorType, NO_ROUTINE_CHECK));
            printf("%.3f\n",  GetVectorElement(Vect, row, &error, errorType, NO_ROUTINE_CHECK));

            if (error) {
                // There is no need to go on.
                break;
            }
        }

        printf("\n");   // Print an additional newline for better formatting.
    }

    return error;   // Return the state of the error flag.
}
