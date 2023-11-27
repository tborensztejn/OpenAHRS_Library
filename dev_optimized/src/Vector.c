#include "../includes/Vector.h"

// Add an example here.
Vector InitVector(Vector *Vect, const uint8_t rows, bool *error) {
    *error = true;  // Set the error flag to true.

    // The routine checks that the pointer to the vector is not null, that the vector is initialised and that there is no buffer overflow.

    // Check if the pointer is not null.
    if (Vect != NULL) {
        // Check if the vector has already been initialized.
        if (!Vect->initialized) {
            // Check if the numbers of rows of the vector will not exceed M_MAX.
            if (IsValidRow(rows)) {
                Vect->rows = rows;          // Set the number of rows of the new vector.
                Vect->initialized = true;   // Set the initialization flag to true.

                *error = false; // Set the error flag to false.
            } else {
                // The number of rows of the vector will exceed M_MAX.
                printf("The number of rows of the vector will exceed M_MAX (err 3).\n");
                // Some code here.
            }
        } else {
            // The vector passed as a parameter to the function via a pointer has already been initialized.
            printf("The vector passed as a parameter to the function via a pointer has already been initialized (err 2).\n");
            // Some code here.
        }
    } else {
        // The pointer is null.
        //printf("The pointer is null. (msg 1).\n");
        //Vector NewVector = VECTOR_INITIALIZER;
        CreateVector(NewVector);

        if (IsValidRow(rows)) {
            NewVector.rows = rows;          // Set the number of rows of the new vector.
            NewVector.initialized = true;   // Set the initialization flag to true.

            *error = false;
        } else {
            // The number of rows of the vector will exceed M_MAX.
            printf("The number of rows of the vector will exceed M_MAX (err 1).\n");
            // Some code here.
        }

        return NewVector;   // Return the initialized new vector.
    }
}

// Add an example here.
bool SetVectorElement(Vector *Vect, const uint8_t row, const float value, const bool check) {
    bool error = true;  // Initialize the error flag to true.

    // The routine checks that the pointer to the vector is not zero, that the vector is initialised and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer is not null.
        if (Vect != NULL) {
            // Check if the vector is initialized.
            if (Vect->initialized) {
                // Check if the row exists (to prevent buffer overflow).
                if (IsValidRow(row)) {
                    // Check if the value is valid.
                    if (!isnan(value)) {
                        Vect->elements[row] = value;    // Set the value of the specified element in the vector.
                        error = false;                  // Set the error flag to false.
                    } else {
                        // The value is not valid.
                        printf("The value is not valid (6).\n");
                        // Some code here.
                    }
                } else {
                    // The row does not exist.
                    printf("The row does not exist (5).\n");
                    // Some code here.
                }
            } else {
                // The vector is not initialized.
                printf("The vector is not initialized (4).\n");
                // Some code here.
            }
        } else {
            // The pointer is null.
            printf("The pointer is null (3).\n");
            // Some code here.
        }
    } else {
        // Bypassing the routine verifications.
        // Check if the value is valid.
        if (!isnan(value)) {
            Vect->elements[row] = value;    // Set the value of the specified element in the vector.
            error = false;                  // Set the error flag to false.
        } else {
            // The value is not valid.
            printf("The value is not valid (7).\n");
            // Some code here.
        }
    }

    return error;   // Return the state of the error flag.
}

// Add an example here.
float GetVectorElement(const Vector *const Vect, const uint8_t row, bool *error, const bool check) {
    float element;  // Declare the variable that will store the returned value.
    *error = true;  // Set the error flag to true.

    // The routine checks that the pointer to the vector is not zero, that the vector is initialised and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer is not null.
        if (Vect != NULL) {
            // Check if the vector is initialized.
            if (Vect->initialized) {
                // Check if the row exists (to prevent buffer overflow).
                if (IsValidRow(row)) {
                    element = Vect->elements[row];  // Retrieve the value of the specified element from the vector.

                    // Check if the element is valid.
                    if (!isnan(element)) {
                        *error = false; // Set the error to false.
                    } else {
                        // The element is not valid.
                        printf("The value is not valid (11).\n");
                        // Some code here.
                    }
                } else {
                    // The row does not exist.
                    printf("The row does not exist (10).\n");
                    element = NAN;
                    // Some code here.
                }
            } else {
                // The vector is not initialized.
                printf("The vector is not initialized (9).\n");
                element = NAN;
            }
        } else {
            // The pointer is null.
            printf("The pointer is null (8).\n");
            element = NAN;
        }
    } else {
        // Bypassing the routine verifications.
        element = Vect->elements[row];  // Retrieve the value of the specified element from the vector.

        // Check if the element is valid.
        if (!isnan(element)) {
            *error = false; // Set the error flag to false.
        } else {
            // The element is not valid.
            printf("The value is not valid (12).\n");
            // Some code here.
        }
    }

    return element; // Return the value of the specified element from the vector.
}

// Add an example here.
bool FillVector(Vector *Vect, const float value, const bool check) {
    bool error = true;  // Initialize the error flag to true.

    // The routine checks that the pointer to the vector is not zero, that the vector is initialised and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer is not null.
        if (Vect != NULL) {
            // Check if the vector is initialized.
            if (Vect->initialized) {
                // Check if the number of rows of the vector do not exceed M_MAX (to prevent buffer overflow).
                if (IsValidRow(Vect->rows)) {
                    // Assign the value to each element of the vector.
                    for (uint8_t row = 0; row < Vect->rows; row++) {
                        // There is not need to check if the value is valid.
                        // Even if NO_ROUTINE_CHECK is used when calling SetVectorElement(), the function still returns an error if the value is invalid.
                        error = SetVectorElement(Vect, row, value, NO_ROUTINE_CHECK);

                        if (error) {
                            // There is no need to go on.
                            printf("There is no need to go on (16).\n");
                            break;
                        }
                    }
                } else {
                    // The number of rows of the vector exceeds M_MAX.
                    printf("The number of rows of the vector exceeds M_MAX (15).\n");
                    // Some code here.
                }
            } else {
                // The vector is not initialized.
                printf("The vector is not initialized (14).\n");
                // Some code here.
            }
        } else {
            // The pointer is null.
            printf("The pointer is null (13).\n");
            // Some code here.
        }
    } else {
        // Bypassing the routine verifications.
        // Assign the value to each element of the vector.
        for (uint8_t row = 0; row < Vect->rows; row++) {
            error = SetVectorElement(Vect, row, value, NO_ROUTINE_CHECK);

            if (error) {
                // There is no need to go on.
                printf("There is no need to go on (17).\n");
                break;
            }
        }
    }

    return error;   // Return the state of the error flag.
}

// Add an example here.
bool CopyVector(const Vector *const VectA, Vector *VectB, const bool check) {
    bool error = true;  // Initialize the error flag to true.

    // The routine checks that the pointers to the vectors are not null, that the vectors are initialised and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer to the vector A is not null.
        if (VectA != NULL) {
            // Check if the pointer to the vector B is not null.
            if (VectB != NULL) {
                // Check if the vector A is initialized.
                if (VectA->initialized) {
                    // Check if the vector B is initialized.
                    if (VectB->initialized) {
                        // Check if the number of rows of the vector A do not exceed M_MAX (to prevent buffer overflow).
                        if (IsValidRow(VectA->rows)) {
                            // Check if the number of rows of the vector B do not exceed M_MAX (to prevent buffer overflow).
                            if (IsValidRow(VectB->rows)) {
                                // Check if vectors A and B have the same dimensions.
                                if (AreSameSizeV(VectA, VectB, &error, NO_ROUTINE_CHECK)) {
                                    if (!error) {
                                        // Iterate through each element and copy it from vector A to vector B.
                                        for (uint8_t row = 0; row < VectA->rows; row++) {
                                            float element = GetVectorElement(VectA, row, &error, NO_ROUTINE_CHECK);

                                            if (!error) {
                                                error = SetVectorElement(VectB, row, element, NO_ROUTINE_CHECK);

                                                if (error) {
                                                    // There is no need to go on.
                                                    printf("There is no need to go on ().");
                                                    break;
                                                }
                                            } else {
                                                // There is no need to go on.
                                                printf("There is no need to go on ().");
                                                break;
                                            }
                                        }
                                    } else {
                                        // An error was encountered when checking the similarity of the dimensions of vectors A and B.
                                        printf("An error was encountered when checking the similarity of the dimensions of vectors A and B ().\n");
                                        // Some code here.
                                    }
                                } else {
                                    // The vectors A and B do not have the same dimensions.
                                    printf("The vectors A and B do not have the same dimensions ().\n");
                                    // Some code here.
                                }
                            } else {
                                // The number of rows of the vector B exceed M_MAX.
                                printf("The number of rows of the vector B exceed M_MAX ().\n");
                                // Some code here.
                            }
                        } else {
                            // The number of rows of the vector A exceed M_MAX.
                            printf("The number of rows of the vector A exceed M_MAX ().\n");
                            // Some code here.
                        }
                    } else {
                        // The vector B is not initialized.
                        printf("The vector B is not initialized ().\n");
                        // Some code here.
                    }
                } else {
                    // The vector A is not initialized.
                    printf("The vector A is not initialized ().\n");
                    // Some code here.
                }
            } else {
                // The pointer to the vector B is null.
                printf("The pointer to the vector B is null ().\n");
                // Some code here.
            }
        } else {
            // The pointer to the vector A is null.
            printf("The pointer to the vector A is null ().\n");
            // Some code here.
        }
    } else {
        // Bypassing the routine verifications.
        // Check if vectors A and B have the same dimensions.
        if (AreSameSizeV(VectA, VectB, &error, NO_ROUTINE_CHECK)) {
            if (!error) {
                // Iterate through each element and copy it from vector A to vector B.
                for (uint8_t row = 0; row < VectA->rows; row++) {
                    float element = GetVectorElement(VectA, row, &error, NO_ROUTINE_CHECK);

                    if (!error) {
                        error = SetVectorElement(VectB, row, element, NO_ROUTINE_CHECK);

                        if (error) {
                            // There is no need to go on.
                            printf("There is no need to go on ().");
                            break;
                        }
                    } else {
                        // There is no need to go on.
                        printf("There is no need to go on ().");
                        break;
                    }
                }
            } else {
                // An error was encountered when checking the similarity of the dimensions of vectors A and B.
                printf("An error was encountered when checking the similarity of the dimensions of vectors A and B ().\n");
                // Some code here.
            }
        } else {
            // The vectors A and B do not have the same dimensions.
            printf("The vectors A and B do not have the same dimensions ().\n");
            // Some code here.
        }
    }

    return error;   // Return the state of the error flag.
}

// Add an example here.
bool AreEqualV(const Vector *const VectA, const Vector *const VectB, bool *error, const float deviation, const bool check) {
    bool areEqual = false;  // Initialize the result to false.
    *error = true;          // Set the error flag to true.

    // The routine checks that the pointers to the vectors are not null, that the vectors are initialised and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer to the vector A is not null.
        if (VectA != NULL) {
            // Check if the pointer to the vector B is not null.
            if (VectB != NULL) {
                // Check if the vector A is initialized.
                if (VectA->initialized) {
                    // Check if the vector B is initialized.
                    if (VectB->initialized) {
                        // Check if the number of rows of the vector A do not exceed M_MAX (to prevent buffer overflow).
                        if (IsValidRow(VectA->rows)) {
                            // Check if the number of rows of the vector B do not exceed M_MAX (to prevent buffer overflow).
                            if (IsValidRow(VectB->rows)) {
                                // Iterate through each element and check if they are close within the deviation.
                                for (uint8_t row = 0; row < VectA->rows; row++) {
                                    // Retrieve the value of the specified element from the vector A.
                                    float elementA = GetVectorElement(VectA, row, error, NO_ROUTINE_CHECK);

                                    // Check if the value of the element of the vector A is valid.
                                    // Even if NO_ROUTINE_CHECK is used when calling GetVectorElement(), the function still returns an error if the value is invalid.
                                    if (!error) {
                                        // Retrieve the value of the specified element from the vector B.
                                        float elementB = GetVectorElement(VectB, row, error, NO_ROUTINE_CHECK);

                                        // Check if the value of the element of the vector B is valid.
                                        // Even if NO_ROUTINE_CHECK is used when calling GetVectorElement(), the function still returns an error if the value is invalid.
                                        if (!error) {
                                            areEqual = CloseAll(elementA, elementB, deviation);

                                            if (!areEqual) {
                                                // The two vectors are different.
                                                // There is no need to go on.
                                                break;
                                            }
                                        } else {
                                            // The value of the element of the vector B is not valid.
                                            // There is no need to go on.
                                            break;
                                            // Some code here.
                                        }
                                    } else {
                                        // The value of the element of the vector A is not valid.
                                        // There is no need to go on.
                                        break;
                                        // Some code here.
                                    }
                                }
                            } else {
                                // The number of rows of the vector B exceed M_MAX.
                                printf("The number of rows of the vector B exceed M_MAX ().\n");
                                // Some code here.
                            }
                        } else {
                            // The number of rows of the vector A exceed M_MAX.
                            printf("The number of rows of the vector A exceed M_MAX ().\n");
                            // Some code here.
                        }
                    } else {
                        // The vector B is not initialized.
                        printf("The vector B is not initialized ().\n");
                        // Some code here.
                    }
                } else {
                    // The vector A is not initialized.
                    printf("The vector A is not initialized ().\n");
                    // Some code here.
                }
            } else {
                // The pointer to the vector B is null.
                printf("The pointer to the vector B is null ().\n");
                // Some code here.
            }
        } else {
            // The pointer to the vector A is null.
            printf("The pointer to the vector A is null ().\n");
            // Some code here.
        }
    } else {
        // Bypassing the routine verifications.
        // Iterate through each element and check if they are close within the deviation.
        for (uint8_t row = 0; row < VectA->rows; row++) {
            // Retrieve the value of the specified element from the vector A.
            float elementA = GetVectorElement(VectA, row, error, NO_ROUTINE_CHECK);

            // Check if the value of the element of the vector A is valid.
            // Even if NO_ROUTINE_CHECK is used when calling GetVectorElement(), the function still returns an error if the value is invalid.
            if (!error) {
                // Retrieve the value of the specified element from the vector B.
                float elementB = GetVectorElement(VectB, row, error, NO_ROUTINE_CHECK);

                // Check if the value of the element of the vector A is valid.
                // Even if NO_ROUTINE_CHECK is used when calling GetVectorElement(), the function still returns an error if the value is invalid.
                if (!error) {
                    areEqual = CloseAll(elementA, elementB, deviation);

                    if (!areEqual) {
                        // The two vectors are different.
                        // There is no need to go on.
                        break;
                    }
                } else {
                    // The value of the element of the vector B is not valid.
                    // There is no need to go on.
                    break;
                    // Some code here.
                }
            } else {
                // The value of the element of the vector A is not valid.
                // There is no need to go on.
                break;
                // Some code here.
            }
        }
    }

    return areEqual;   // Return the result.
}

// Add an example here.
bool AreSameSizeV(const Vector *const VectA, const Vector *const VectB, bool *error, const bool check) {
    bool areSameSize = false;   // Initialize the result to false.
    *error = true;              // Set the error flag to true.

    // The routine checks that the pointers to the vectors are not null, that the vectors are initialised and that there is no buffer overflow.

    // Check if routine verifications need to be done.
    if (check) {
        // Check if the pointer to the vector A is not null.
        if (VectA != NULL) {
            // Check if the pointer to the vector B is not null.
            if (VectB != NULL) {
                // Check if the vector A is initialized.
                if (VectA->initialized) {
                    // Check if the vector B is initialized.
                    if (VectB->initialized) {
                        // Check if the number of rows of the vector A do not exceed M_MAX (to prevent buffer overflow).
                        if (IsValidRow(VectA->rows)) {
                            // Check if the number of rows of the vector B do not exceed M_MAX (to prevent buffer overflow).
                            if (IsValidRow(VectB->rows)) {
                                // Check if vector A has the same number of rows as vector B.
                                if (VectA->rows == VectB->rows) {
                                    areSameSize = true;
                                    *error = false;
                                } else {
                                    // The vector A has not the same number of rows as vector B.
                                    // Some code here.
                                }
                            } else {
                                // The number of rows of the vector B exceed M_MAX.
                                printf("The number of rows of the vector B exceed M_MAX ().\n");
                                // Some code here.
                            }
                        } else {
                            // The number of rows of the vector A exceed M_MAX.
                            printf("The number of rows of the vector A exceed M_MAX ().\n");
                            // Some code here.
                        }
                    } else {
                        // The vector B is not initialized.
                        printf("The vector B is not initialized ().\n");
                        // Some code here.
                    }
                } else {
                    // The vector A is not initialized.
                    printf("The vector A is not initialized ().\n");
                    // Some code here.
                }
            } else {
                // The pointer to the vector B is null.
                printf("The pointer to the vector B is null ().\n");
                // Some code here.
            }
        } else {
            // The pointer to the vector A is null.
            printf("The pointer to the vector A is null ().\n");
            // Some code here.
        }
    } else {
        // Bypassing the routine verifications.
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

bool PrintVector(const Vector *const Vect, const bool check) {
    bool error = true;  // Initialize the error to true.

    if (check) {
        // Check if the pointer is not null.
        if (Vect != NULL) {
            // Check if the vector is initialized.
            if (Vect->initialized) {
                // Check if the numbers of rows of the vector do not exceed M_MAX (to prevent buffer overflow).
                if (IsValidRow(Vect->rows)) {
                    // Iterate through each element and print it and move to the next row with a newline character.
                    for (uint8_t row = 0; row < Vect->rows; row++) {
                        //printf("%.5f\n",  GetVectorElement(Vect, row, &error, NO_ROUTINE_CHECK));
                        printf("%.3f\n",  GetVectorElement(Vect, row, &error, NO_ROUTINE_CHECK));

                        if (error) {
                            // There is no need to go on.
                            break;
                        }
                    }

                    printf("\n");   // Print an additional newline for better formatting.
                } else {
                    // The row does not exist.
                    // Some code here.
                }
            } else {
                // The pointer is null.
                // Some code here.
            }
        } else {
            // The vector is not initialized.
            // Some code here.
        }
    } else {
        // Bypassing the routine verifications.
        // Iterate through each element and print it and move to the next row with a newline character.
        for (uint8_t row = 0; row < Vect->rows; row++) {
            //printf("%.5f\n",  GetVectorElement(Vect, row, &error, NO_ROUTINE_CHECK));
            printf("%.3f\n",  GetVectorElement(Vect, row, &error, NO_ROUTINE_CHECK));

            if (error) {
                // There is no need to go on.
                break;
            }
        }

        printf("\n");   // Print an additional newline for better formatting.
    }

    return error;   // Return the state of the error flag.
}
