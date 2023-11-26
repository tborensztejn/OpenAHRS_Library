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

    /* InitVector() function test (test passed successfully). */
    printf("InitVector() function test.\n");
    Vector Vect1 = InitVector(NULL, rows, &error);
    PrintfBool(error);
    // Deliberately generate error.
    Vector Vect2 = InitVector(NULL, MAX_M + 1, &error);
    PrintfBool(error);
    // The code below is the same as the code above.
    CreateVector(Vect3);
    InitVector(&Vect3, rows, &error);
    PrintfBool(error);
    // Deliberately generate error.
    CreateVector(Vect4);
    InitVector(&Vect4, MAX_M + 1, &error);
    PrintfBool(error);
    printf("\n");

    /* SetVectorElement() function test (test passed successfully). */
    printf("SetVectorElement() function test.\n");
    const uint8_t row = 0;
    Vector Vect5 = InitVector(NULL, rows, &error);
    error = SetVectorElement(&Vect5, row, 1.0f, CHECK);
    PrintfBool(error);
    // Deliberately generate error.
    error = SetVectorElement(&Vect5, MAX_M + 1, 1.0f, CHECK);
    PrintfBool(error);
    // Deliberately generate error.
    Vector Vect6;
    error = SetVectorElement(&Vect6, row, 1.0f, CHECK);
    PrintfBool(error);
    // Deliberately generate error.
    Vector *Vect7 = NULL;
    error = SetVectorElement(Vect7, row, 1.0f, CHECK);
    PrintfBool(error);
    // Deliberately generate error.
    Vector Vect8 = InitVector(NULL, rows, &error);
    error = SetVectorElement(&Vect8, MAX_M + 1, 1.0f, CHECK);
    PrintfBool(error);
    // Deliberately generate error.
    Vector Vect9 = InitVector(NULL, rows, &error);
    error = SetVectorElement(&Vect9, row, NAN, CHECK);
    PrintfBool(error);
    // Deliberately generate error.
    Vector Vect10 = InitVector(NULL, rows, &error);
    error = SetVectorElement(&Vect10, row, NAN, NO_CHECK);
    PrintfBool(error);
    printf("\n");

    /* GetVectorElement() function test (test passed successfully). */
    printf("GetVectorElement() function test.\n");
    float value = 0.0f;
    Vector Vect11 = InitVector(NULL, rows, &error);
    error = SetVectorElement(&Vect11, row, 1.0f, CHECK);
    value = GetVectorElement(&Vect11, row, &error, CHECK);
    printf("%f\n", value);

    // Some code here.

    return error;
}
