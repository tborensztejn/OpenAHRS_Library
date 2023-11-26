#include "../includes/Linalg.h"

void PrintfBool(bool var) {
    if (var) {
        printf("true\n");
    } else {
        printf("false\n");
    }
}

int main() {
    /* The purpose of this code is to test the operation of the functions in the "Linalg" library. */

    #define M   3   // This value must be less than or equal to MAX_M.
    #define N   3   // This value must be less than or equal to MAX_N.

    #if M > MAX_M
        #error "M exceeds the maximum allowed value."
    #endif

    #if N > MAX_N
        #error "N exceeds the maximum allowed value."
    #endif

    bool error = false;

    const uint8_t rows = M;
    const uint8_t cols = N;

    Matrix Mat = InitMatrix(NULL, rows, cols);
    //Matrix Mat;   // Deliberately generate errors.
    error = PrintMatrix(&Mat);
    PrintfBool(error);
    error = FillIdentityMatrix(&Mat);
    PrintfBool(error);
    error = PrintMatrix(&Mat);
    PrintfBool(error);
    float value = 2.0f;
    error = FillMatrix(&Mat, value);
    PrintfBool(error);
    error = PrintMatrix(&Mat);
    PrintfBool(error);

    /*
    // The code below is the same as the code above.
    CreateMatrix(Mat);
    InitMatrix(&Mat, rows, cols);
    error = PrintMatrix(&Mat);
    PrintfBool(error);
    error = FillIdentityMatrix(&Mat);
    PrintfBool(error);
    error = PrintMatrix(&Mat);
    PrintfBool(error);
    float value = 2.0f;
    error = FillMatrix(&Mat, value);
    PrintfBool(error);
    error = PrintMatrix(&Mat);
    PrintfBool(error);
    */

    // Some code here.

    return error;
}
