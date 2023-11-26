#include "../includes/Vector.h"

// Add an example here.
Vector InitVector(Vector *Vect, const uint8_t rows, bool *error) {
    *error = true;  // Initialize the error to true.

    // Check if the numbers of rows of the vector will not exceed M_MAX.
    if (IsValidRow(rows)) {
        // Check if the pointer is not null.
        if (Vect != NULL) {
            // Check if the vector has already been initialized.
            if (!Vect->initialized) {
                Vect->rows = rows;          // Set the number of rows of the new vector.
                Vect->initialized = true;   // Set the initialization flag to true.

                *error = false;
            } else {
                // The vector passed as a parameter to the function via a pointer has already been initialized.
                printf("The vector passed as a parameter to the function via a pointer has already been initialized.\n");
                // Some code here.
            }
        } else {
            // The pointer is null.
            //Vector NewVector = VECTOR_INITIALIZER;
            CreateVector(NewVector);

            NewVector.rows = rows;          // Set the number of rows of the new vector.
            NewVector.initialized = true;   // Set the initialization flag to true.

            *error = false;

            return NewVector;               // Return the initialized new vector.
        }
    } else {
        // The numbers of rows of the vector will exceed M_MAX.
        printf("The numbers of rows of the vector will exceed M_MAX.\n");
        // Some code here.
    }
}

// Add an example here.
bool SetVectorElement(Vector *Vect, const uint8_t row, const float value, const bool check) {
    bool error = true;  // Initialize the error to true.

    if (check) {
        // Check if the row exists (to prevent buffer overflow).
        if (IsValidRow(row)) {
            // Check if the pointer is not null.
            if (Vect != NULL) {
                // Check if the vector is initialized.
                if (Vect->initialized) {
                    // Check if the value is valid.
                    if (!isnan(value)) {
                        Vect->elements[row] = value;    // Set the value of the specified element in the vector.
                        error = false;                  // Set the error to false.
                    } else {
                        // The value is not valid.
                        printf("The value is not valid.\n");
                        // Some code here.
                    }
                } else {
                    // The vector is not initialized.
                    printf("The vector is not initialized.\n");
                    // Some code here.
                }
            } else {
                // The pointer is null.
                printf("The pointer is null.\n");
                // Some code here.
            }
        } else {
            // The row do not exists.
            printf("The row do not exists.\n");
            // Some code here.
        }
    } else {
        // Bypassing the routine checks.
        // Check if the value is valid.
        if (!isnan(value)) {
            Vect->elements[row] = value;    // Set the value of the specified element in the vector.
            error = false;                  // Set the error to false.
        } else {
            // The value is not valid.
            printf("The value is not valid.\n");
            // Some code here.
        }
    }

    return error;   // Return the error status.
}

// Add an example here.
float GetVectorElement(const Vector *const Vect, const uint8_t row, bool *error, const bool check) {
    float element;  // Declare the variable that will store the returned value.
    *error = true;  // Initialize the error to true.

    if (check) {
        // Check if the row exists (to prevent buffer overflow).
        if (IsValidRow(row)) {
            // Check if the pointer is not null.
            if (Vect != NULL) {
                // Check if the vector is initialized.
                if (Vect->initialized) {
                    element = Vect->elements[row];  // Retrieve the value of the specified element from the vector.
                    *error = false;                 // Set the error to false.
                } else {
                    // The vector is not initialized.
                    printf("The vector is not initialized.\n");
                    element = NAN;
                }
            } else {
                // The pointer is null.
                printf("The pointer is null.\n");
                element = NAN;
            }
        } else {
            // The row do not exists.
            printf("The row do not exists.\n");
            element = NAN;
            // Some code here.
        }
    } else {
        // Bypassing the routine checks.
        element = Vect->elements[row];  // Retrieve the value of the specified element from the vector.
        *error = false;                 // Set the error to false.
    }

    return element; // Return the value of the specified element from the vector.
}

// Add an example here.
bool FillVector(Vector *Vect, const float value, const bool check) {
    bool error = true;  // Initialize the error to true.

    if (check) {
        // Check if the numbers of rows of the vector do not exceed M_MAX (to prevent buffer overflow).
        if (IsValidRow(Vect->rows)) {
            // Check if the pointer is not null.
            if (Vect != NULL) {
                // Check if the vector is initialized.
                if (Vect->initialized) {
                    // Assign the value to each element of the vector.
                    for (uint8_t row = 0; row < Vect->rows; row++) {
                        error = SetVectorElement(Vect, row, value, NO_CHECK);
                    }
                } else {
                    // The vector is not initialized.
                    // Some code here.
                }
            } else {
                // The pointer is null.
                // Some code here.
            }

        } else {
            // The row do not exists.
            // Some code here.
        }
    } else {
        // Bypassing the routine checks.
        // Assign the value to each element of the vector.
        for (uint8_t row = 0; row < Vect->rows; row++) {
            error = SetVectorElement(Vect, row, value, NO_CHECK);
        }
    }

    return error;   // Return the error status.
}

// Add an example here.
bool CopyVector(const Vector *const VectA, Vector *VectB, const bool check) {
    bool error = true;  // Initialize the error to true.

    if (check) {
        // Check if the numbers of rows of the vector A do not exceed M_MAX (to prevent buffer overflow).
        if (IsValidRow(VectA->rows)) {
            // Check if the numbers of rows of the vector B do not exceed M_MAX (to prevent buffer overflow).
            if (IsValidRow(VectB->rows)) {
                // Check if the pointer to the vector A is not null.
                if (VectA != NULL) {
                    // Check if the pointer to the vector B is not null.
                    if (VectB != NULL) {
                        // Check if the vector A is initialized.
                        if (VectA->initialized) {
                            // Check if the vector B is initialized.
                            if (VectB->initialized) {
                                // Check if vectors A and B have the same dimensions.
                                if (AreSameSizeV(VectA, VectB, &error, NO_CHECK)) {
                                    if (!error) {
                                        // Iterate through each element and copy it from vector A to vector B.
                                        for (uint8_t row = 0; row < VectA->rows; row++) {
                                            float element = GetVectorElement(VectA, row, &error, NO_CHECK);

                                            if (!error) {
                                                error = SetVectorElement(VectB, row, element, NO_CHECK);

                                                if (error) {
                                                    // There's no need to go on.
                                                    break;
                                                }
                                            } else {
                                                // There's no need to go on.
                                                break;
                                            }
                                        }
                                    } else {
                                        // An error was encountered when checking if the dimensions of the vector A and B are the same or not.
                                        // Some code here.
                                    }
                                } else {
                                    // The vectors A and B do not have the same dimensions.
                                    // Some code here.
                                }
                            } else {
                                // The vector B is not initialized.
                                // Some code here.
                            }
                        } else {
                            // The vector A is not initialized.
                            // Some code here.
                        }
                    } else {
                        // The pointer to the vector B is null.
                        // Some code here.
                    }
                } else {
                    // The pointer to the vector A is null.
                    // Some code here.
                }
            } else {
                // The numbers of rows of the vector B exceed M_MAX.
                // Some code here.
            }
        } else {
            // The numbers of rows of the vector A exceed M_MAX.
            // Some code here.
        }
    } else {
        // Bypassing the routine checks.
        // Check if vectors A and B have the same dimensions.
        if (AreSameSizeV(VectA, VectB, &error, NO_CHECK)) {
            if (!error) {
                // Iterate through each element and copy it from vector A to vector B.
                for (uint8_t row = 0; row < VectA->rows; row++) {
                    float element = GetVectorElement(VectA, row, &error, NO_CHECK);

                    if (!error) {
                        error = SetVectorElement(VectB, row, element, NO_CHECK);

                        if (error) {
                            // There's no need to go on.
                            break;
                        }
                    } else {
                        // There's no need to go on.
                        break;
                    }
                }
            } else {
                // An error was encountered when checking if the dimensions of the vector A and B are the same or not.
                // Some code here.
            }
        } else {
            // The vectors A and B do not have the same dimensions.
            // Some code here.
        }
    }

    return error;
}

// Add an example here.
bool AreEqualV(const Vector *const VectA, const Vector *const VectB, bool *error, const float deviation, const bool check) {
    bool areEqual = false;   // Initialize the result to false.
    *error = true;              // Initialize the error to true.

    if (check) {
        // Check if the numbers of rows of the vector A do not exceed M_MAX (to prevent buffer overflow).
        if (IsValidRow(VectA->rows)) {
            // Check if the numbers of rows of the vector B do not exceed M_MAX (to prevent buffer overflow).
            if (IsValidRow(VectB->rows)) {
                // Check if the pointer to the vector A is not null.
                if (VectA != NULL) {
                    // Check if the pointer to the vector B is not null.
                    if (VectB != NULL) {
                        // Check if the vector A is initialized.
                        if (VectA->initialized) {
                            // Check if the vector B is initialized.
                            if (VectB->initialized) {
                                // Iterate through each element and check if they are close within the deviation.
                                for (uint8_t row = 0; row < VectA->rows; row++) {
                                    // Need a small update here.
                                    areEqual = CloseAll(GetVectorElement(VectA, row, error, NO_CHECK), GetVectorElement(VectB, row, error, NO_CHECK), deviation);

                                    if (!areEqual) {
                                        // There's no need to go on. The two vectors are different.
                                        break;
                                    }
                                }
                            } else {
                                // The vector B is not initialized.
                                // Some code here.
                            }
                        } else {
                            // The vector A is not initialized.
                            // Some code here.
                        }
                    } else {
                        // The pointer to the vector B is null.
                        // Some code here.
                    }
                } else {
                    // The pointer to the vector A is null.
                    // Some code here.
                }
            } else {
                // The numbers of rows of the vector B exceed M_MAX.
                // Some code here.
            }
        } else {
            // The numbers of rows of the vector A exceed M_MAX.
            // Some code here.
        }
    } else {
        // Bypassing the routine checks.
        // Iterate through each element and check if they are close within the deviation.
        for (uint8_t row = 0; row < VectA->rows; row++) {
            // Need a small update here.
            areEqual = CloseAll(GetVectorElement(VectA, row, error, NO_CHECK), GetVectorElement(VectB, row, error, NO_CHECK), deviation);

            if (!areEqual) {
                // There's no need to go on. The two vectors are different.
                break;
            }
        }
    }

    return areEqual;
}

// Add an example here.
bool AreSameSizeV(const Vector *const VectA, const Vector *const VectB, bool *error, const bool check) {
    bool areSameSize = false;   // Initialize the result to false.
    *error = true;              // Initialize the error to true.

    if (check) {
        // Check if the numbers of rows of the vector A do not exceed M_MAX (to prevent buffer overflow).
        if (IsValidRow(VectA->rows)) {
            // Check if the numbers of rows of the vector B do not exceed M_MAX (to prevent buffer overflow).
            if (IsValidRow(VectB->rows)) {
                // Check if the pointer to the vector A is not null.
                if (VectA != NULL) {
                    // Check if the pointer to the vector B is not null.
                    if (VectB != NULL) {
                        // Check if the vector A is initialized.
                        if (VectA->initialized) {
                            // Check if the vector B is initialized.
                            if (VectB->initialized) {
                                // Check if vector A has the same number of rows as vector B.
                                if (VectA->rows == VectB->rows) {
                                    areSameSize = true;
                                    *error = false;
                                } else {
                                    // The vector A has not the same number of rows as vector B.
                                    // Some code here.
                                }
                            } else {
                                // The vector B is not initialized.
                                // Some code here.
                            }
                        } else {
                            // The vector A is not initialized.
                            // Some code here.
                        }
                    } else {
                        // The pointer to the vector B is null.
                        // Some code here.
                    }
                } else {
                    // The pointer to the vector A is null.
                    // Some code here.
                }
            } else {
                // The numbers of rows of the vector B exceed M_MAX.
                // Some code here.
            }
        } else {
            // The numbers of rows of the vector A exceed M_MAX.
            // Some code here.
        }
    } else {
        // Bypassing the routine checks.
        // Check if vector A has the same number of rows as vector B.
        if (VectA->rows == VectB->rows) {
            areSameSize = true;
            *error = false;
        } else {
            // The vector A has not the same number of rows as vector B.
            // Some code here.
        }
    }

    return areSameSize;
}

bool PrintVector(const Vector *const Vect, const bool check) {
    bool error = true;  // Initialize the error to true.

    if (check) {
        // Check if the numbers of rows of the vector do not exceed M_MAX (to prevent buffer overflow).
        if (IsValidRow(Vect->rows)) {
            // Check if the pointer is not null.
            if (Vect != NULL) {
                // Check if the vector is initialized.
                if (Vect->initialized) {
                    // Iterate through each element and print it and move to the next row with a newline character.
                    for (uint8_t row = 0; row < Vect->rows; row++) {
                        //printf("%.5f\n",  GetVectorElement(Vect, row, &error, NO_CHECK));
                        printf("%.3f\n",  GetVectorElement(Vect, row, &error, NO_CHECK));

                        if (error) {
                            // There's no need to go on.
                            break;
                        }
                    }

                    printf("\n");   // Print an additional newline for better formatting.
                } else {
                    // The vector is not initialized.
                    // Some code here.
                }
            } else {
                // The pointer is null.
                // Some code here.
            }

        } else {
            // The row do not exists.
            // Some code here.
        }
    } else {
        // Bypassing the routine checks.
        // Iterate through each element and print it and move to the next row with a newline character.
        for (uint8_t row = 0; row < Vect->rows; row++) {
            //printf("%.5f\n",  GetVectorElement(Vect, row, &error, NO_CHECK));
            printf("%.3f\n",  GetVectorElement(Vect, row, &error, NO_CHECK));

            if (error) {
                // There's no need to go on.
                break;
            }
        }

        printf("\n");   // Print an additional newline for better formatting.
    }

    return error;   // Return the error status.
}
