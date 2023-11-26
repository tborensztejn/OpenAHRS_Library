#include "../includes/Vector.h"

// Add an example here.
Vector InitVector(Vector *Vect, const uint8_t rows) {
    // Check if the pointer is not null.
    if (Vect != NULL) {
        // Check if the vector has already been initialized.
        if (!Vect->initialized) {
            Vect->rows = rows;          // Set the number of rows of the new vector.
            Vect->initialized = true;   // Set the initialization flag to true.
        } else {
            // The vector passed as a parameter to the function via a pointer has already been initialized.
            // Some code here.
        }
    } else {
        // The pointer is null.
        //Vector NewVector = VECTOR_INITIALIZER;
        CreateVector(NewVector);

        NewVector.rows = rows;          // Set the number of rows of the new vector.
        NewVector.initialized = true;   // Set the initialization flag to true.

        return NewVector;               // Return the initialized new vector.
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
                    if (value != NAN) {
                        Vect->elements[row] = value;    // Set the value of the specified element in the vector.
                        error = false;                  // Set the error to false.
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
        // Bypassing the checks.
        // Check if the value is valid.
        if (value != NAN) {
            Vect->elements[row] = value;    // Set the value of the specified element in the vector.
            error = false;                  // Set the error to false.
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
                    element = NAN;
                }
            } else {
                // The pointer is null.
                element = NAN;
            }
        } else {
            // The row do not exists.
            element = NAN;
            // Some code here.
        }
    } else {
        // Bypassing the checks.
        element = Vect->elements[row];  // Retrieve the value of the specified element from the vector.
        *error = false;                 // Set the error to false.
    }

    return element; // Return the value of the specified element from the vector.
}

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
        // Bypassing the checks.
        // Some code here.
    }

    return error;   // Return the error status.
}
