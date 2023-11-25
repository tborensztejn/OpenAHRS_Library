#include "Linalg.h"
#include "../includes/Utils.h"

#define MATRIX_INITIALIZER { \
    .rows = 0, \
    .cols = 0, \
    .elements = {0}, \
    .initialized = false \
} \

#define VECTOR_INITIALIZER { \
    .rows = 0, \
    .elements = {0}, \
    .initialized = false \
} \

#define MAX_M   4   // Maximum number of rows in a matrix.
#define MAX_N   4   // Maximum number of columns in a matrix.

typedef struct {
    uint8_t rows;
    uint8_t cols;
    float elements[MAX_M * MAX_N];
    bool initialized;
} Matrix;

typedef struct {
    uint8_t rows;
    float elements[MAX_M];
} Vector;

Matrix InitMatrix(const uint8_t rows, const uint8_t cols) {
    Matrix NewMatrix = MATRIX_INITIALIZER;

    NewMatrix.rows = rows;
    NewMatrix.cols = cols;

    return NewMatrix;
}

int main() {
    const uint8_t rows = 3;
    const uint8_t cols = 3;

    Matrix Mat = InitMatrix(rows, cols);

    // Some code here.

    return 0;
}
