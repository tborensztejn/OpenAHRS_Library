#include "../includes/Vector.h"

// Add an example here.
Vector InitVector(Vector *Vect, const uint8_t rows) {
    // Check if the pointer is not null.
    if (Vect != NULL) {
        // Check if the vector has already been initialized.
        if (!Vect->initialized) {
            Vect->rows = rows;
            Vect->initialized = true;
        } else {
            // The vector passed as a parameter to the function via a pointer has already been initialized.
            // Some code here.
        }
    } else {
        // The pointer is null.
        //Vector NewVector = VECTOR_INITIALIZER;
        CreateVector(NewVector);

        NewVector.rows = rows;
        NewVector.initialized = true;

        return NewVector;
    }
}

// Add an example here.
bool SetVectorElement(Vector *Vect, const uint8_t row, const float value) {
    bool error = true;  // Initialize the error to true.

    // Check if the pointer is not null.
    if (Vect != NULL) {
        // Check if the matrix is initialized.
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

    return error;   // Return the error status.
}

// Add an example here.
float GetVectorElement(const Vector *const Vect, const uint8_t row, bool *error) {
    float element;  // Declare the variable that will store the returned value.
    *error = true;  // Initialize the error to true.

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

    return element; // Return the value of the specified element from the matrix.
}
