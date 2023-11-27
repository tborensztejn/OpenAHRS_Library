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

    #define M   3   // This value must be less than or equal to M_MAX.
    #define N   3   // This value must be less than or equal to N_MAX.

    #if M > M_MAX
        #error "M exceeds the maximum allowed value."
    #endif

    #if N > N_MAX
        #error "N exceeds the maximum allowed value."
    #endif

    bool error = false;

    const uint8_t rows = M;
    const uint8_t cols = N;

    float value = 1.0f;

    /* InitVector() function test (test passed successfully). */
    printf("InitVector() function test.\n");
    Vector Vect1 = InitVector(NULL, rows, &error);
    PrintfBool(error);
    /*
    // The code below is the same as the code above.
    // Warning: never use "Vector newVector;" instruction! Always use "CreateVector(newVector);" instruction.
    CreateVector(Vect1);
    InitVector(&Vect1, rows, &error);
    PrintfBool(error);
    */
    // Deliberately generate error (number of rows will exceed M_MAX).
    Vector Vect2 = InitVector(NULL, M_MAX + 1, &error);
    PrintfBool(error);
    // Deliberately generate error (vector already initialized).
    Vector Vect3 = InitVector(NULL, rows, &error);
    InitVector(&Vect3, rows, &error);
    PrintfBool(error);
    // Deliberately generate error (number of rows will exceed M_MAX).
    CreateVector(Vect4);
    InitVector(&Vect4, M_MAX + 1, &error);
    PrintfBool(error);
    printf("\n");

    /* SetVectorElement() function test (test passed successfully). */
    printf("SetVectorElement() function test.\n");
    const uint8_t row = 0;
    Vector Vect5 = InitVector(NULL, rows, &error);
    error = SetVectorElement(&Vect5, row, value, ROUTINE_CHECK);
    PrintfBool(error);
    // Deliberately generate error (pointer is null).
    Vector *Vect6 = NULL;
    error = SetVectorElement(Vect6, row, value, ROUTINE_CHECK);
    PrintfBool(error);
    // Deliberately generate error (vector not initialized).
    Vector Vect7;
    error = SetVectorElement(&Vect7, row, value, ROUTINE_CHECK);
    PrintfBool(error);
    // Deliberately generate error (row does not exist).
    Vector Vect8 = InitVector(NULL, rows, &error);
    error = SetVectorElement(&Vect8, M_MAX + 1, value, ROUTINE_CHECK);
    PrintfBool(error);
    // Deliberately generate error (value is not valid).
    Vector Vect9 = InitVector(NULL, rows, &error);
    error = SetVectorElement(&Vect9, row, NAN, ROUTINE_CHECK);
    PrintfBool(error);
    // Deliberately generate error (value is not valid).
    Vector Vect10 = InitVector(NULL, rows, &error);
    error = SetVectorElement(&Vect10, row, NAN, NO_ROUTINE_CHECK);
    PrintfBool(error);
    printf("\n");

    /* GetVectorElement() function test (test passed successfully). */
    printf("GetVectorElement() function test.\n");
    Vector Vect11 = InitVector(NULL, rows, &error);
    error = SetVectorElement(&Vect11, row, value, ROUTINE_CHECK);
    value = GetVectorElement(&Vect11, row, &error, ROUTINE_CHECK);
    PrintfBool(error);
    printf("%f\n", value);
    // Deliberately generate error (pointer is null).
    Vector *Vect12 = NULL;
    value = GetVectorElement(Vect12, row, &error, ROUTINE_CHECK);
    PrintfBool(error);
    printf("%f\n", value);
    value = 1.0f;
    // Deliberately generate error (vector not initialized).
    Vector Vect14;
    value = GetVectorElement(&Vect14, row, &error, ROUTINE_CHECK);
    PrintfBool(error);
    printf("%f\n", value);
    value = 1.0f;
    // Deliberately generate error (row does not exist).
    Vector Vect15 = InitVector(NULL, rows, &error);
    value = GetVectorElement(&Vect15, M_MAX + 1, &error, ROUTINE_CHECK);
    PrintfBool(error);
    printf("%f\n", value);
    value = 1.0f;
    // Deliberately generate error (value is not valid).
    Vector Vect16 = InitVector(NULL, rows, &error);
    Vect16.elements[row] = NAN; // Never do that!
    value = GetVectorElement(&Vect16, row, &error, ROUTINE_CHECK);
    PrintfBool(error);
    printf("%f\n", value);
    value = 1.0f;
    // Deliberately generate error (value is not valid).
    Vector Vect17 = InitVector(NULL, rows, &error);
    Vect17.elements[row] = NAN; // Never do that!
    value = GetVectorElement(&Vect17, row, &error, NO_ROUTINE_CHECK);
    PrintfBool(error);
    printf("%f\n", value);
    value = 1.0f;
    printf("\n");

    /* FillVector() function test (test passed successfully). */
    printf("FillVector() function test.\n");
    Vector Vect18 = InitVector(NULL, rows, &error);
    error = FillVector(&Vect18, value, ROUTINE_CHECK);
    PrintfBool(error);
    // Deliberately generate error (pointer is null).
    Vector *Vect19 = NULL;
    error = FillVector(Vect19, value, ROUTINE_CHECK);
    PrintfBool(error);
    // Deliberately generate error (vector not initialized).
    Vector Vect20;
    error = FillVector(&Vect20, value, ROUTINE_CHECK);
    PrintfBool(error);
    // Deliberately generate error (number of rows exceed M_MAX).
    Vector Vect21 = InitVector(NULL, rows, &error);
    Vect21.rows = M_MAX + 1;    // Never do that!
    error = FillVector(&Vect21, value, ROUTINE_CHECK);
    PrintfBool(error);
    // Deliberately generate error (value is not valid).
    Vector Vect22 = InitVector(NULL, rows, &error);
    error = FillVector(&Vect22, NAN, ROUTINE_CHECK);
    PrintfBool(error);// Deliberately generate error (value is not valid).
    Vector Vect23 = InitVector(NULL, rows, &error);
    error = FillVector(&Vect23, NAN, NO_ROUTINE_CHECK);
    PrintfBool(error);
    printf("\n");

    /* FillVector() function test (test passed successfully). */
    printf("FillVector() function test.\n");
    printf("\n");

    /* PrintVector() function test. */
    printf("PrintVector() function test.\n");
    Vector Vect24 = InitVector(NULL, rows, &error);
    error =  PrintVector(&Vect24, ROUTINE_CHECK);
    PrintfBool(error);
    printf("\n");

    // Some code here.

    return error;
}
