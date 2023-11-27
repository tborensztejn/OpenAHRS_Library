#include "../includes/Common.h"

/*** Declaration of functions. ***/

// Add an example here.
bool IsValidRow(const uint8_t row) {
    bool isValid = false;

    // Don't forget that the machine counts from 0 and not 1.
    if (row < M_MAX) {
        isValid = true;
    }

    return isValid;
}

// Add an example here.
bool IsValidCol(const uint8_t col) {
    bool isValid = false;

    // Don't forget that the machine counts from 0 and not 1.
    if (col < N_MAX) {
        isValid = true;
    }

    return isValid;
}
