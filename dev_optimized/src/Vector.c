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
