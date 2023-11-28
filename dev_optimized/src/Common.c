#include "../includes/Common.h"

/*** Declaration of functions. ***/

// Add an example here.
bool IsValidRowsNumber(const uint8_t rows) {
    bool isValid = false;

    if (rows <= M_MAX) {
        isValid = true;
    }

    return isValid;
}

// Add an example here.
bool IsValidColsNumber(const uint8_t cols) {
    bool isValid = false;

    if (cols <= N_MAX) {
        isValid = true;
    }

    return isValid;
}

// Add an example here.
bool IsValidRow(const uint8_t row, const uint8_t rows) {
    bool isValid = false;

    // Don't forget that the machine counts from 0 and not 1.
    if (row < rows) {
        isValid = true;
    }

    return isValid;
}

// Add an example here.
bool IsValidCol(const uint8_t col, const uint8_t cols) {
    bool isValid = false;

    // Don't forget that the machine counts from 0 and not 1.
    if (col < cols) {
        isValid = true;
    }

    return isValid;
}
