#include "../includes/Linalg.h"

void PrintfBool(bool var) {
    if (var) {
        printf("true\n");
        //printf("true");
    } else {
        printf("false\n");
        //printf("false");
    }
}

const char* ErrorTypeToString(ErrorType error) {
    switch (error) {
        case NO_ERROR:            return "NO_ERROR";
        case NULL_PTR:            return "NULL_PTR";
        case UNINITIALIZED:       return "UNINITIALIZED";
        case ALREADY_INIT:        return "ALREADY_INIT";
        case INVALID_ROWS_NUMBER: return "INVALID_ROWS_NUMBER";
        case INVALID_COLS_NUMBER: return "INVALID_COLS_NUMBER";
        case NON_EXISTING_ROW:    return "NON_EXISTING_ROW";
        case NON_EXISTING_COL:    return "NON_EXISTING_COL";
        case SIZE_MISMATCH:       return "SIZE_MISMATCH";
        case INVALID_VALUE:       return "INVALID_VALUE";
        case INVALID_ELEMENT:     return "INVALID_ELEMENT";
        default:                  return "UNKNOWN_ERROR";
    }
}

void RunInitVectorTest(Vector (*initFunc)(Vector*, uint8_t, bool*, ErrorType*), Vector* Vect, uint8_t rows, bool* error, ErrorType* errorType) {
    *Vect = initFunc(NULL, rows, error, errorType);
    printf("Error status: ");
    PrintfBool(*error);
    printf("\t Error type: %s\n\n", ErrorTypeToString(*errorType));
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
    ErrorType errorType = NO_ERROR;

    const uint8_t rows = M;
    const uint8_t cols = N;

    float value = 1.0f;

    /* InitVector() function test (test passed successfully). */
    /*
    printf("InitVector() function test.\n");
    printf("\n");
    printf("Test 1 - No error.\n");
    Vector Vect1;
    RunInitVectorTest(InitVector, &Vect1, rows, &error, &errorType);

    // Deliberately generate error (The number of rows exceeds M_MAX).
    printf("Test 2 - The number of rows exceeds M_MAX.\n");
    Vector Vect2 = ;
    RunInitVectorTest(InitVector, &Vect1, M_MAX + 1, &error, &errorType);
    */

    /* InitVector() function test (test passed successfully). */

    printf("InitVector() function test.\n\n");
    printf("Test 1 - No error.\n");
    Vector Vect1 = InitVector(NULL, rows, &error, &errorType);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    // The code below is the same as the code above.
    // Warning: never use "Vector newVector;" instruction! Always use "CreateVector(newVector);" instruction.
    /*
    printf("Test 1 - No error.\n");
    CreateVector(Vect1);
    InitVector(&Vect1, rows, &error, &errorType);
    printf("Error status: ");
    PrintfBool(error);
    printf("\t Error type: %s\n\n", ErrorTypeToString(errorType));
    */

    // Deliberately generate error (The number of rows exceeds M_MAX).
    printf("Test 2 - The number of rows exceeds M_MAX.\n");
    Vector Vect2 = InitVector(NULL, M_MAX + 1, &error, &errorType);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    // Deliberately generate error (The vector has already been initialized).
    printf("Test 3 - The vector has already been initialized.\n");
    Vector Vect3 = InitVector(NULL, rows, &error, &errorType);
    InitVector(&Vect3, rows, &error, &errorType);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    // Deliberately generate error (The number of rows exceeds M_MAX).
    printf("Test 4 - The number of rows exceeds M_MAX.\n");
    CreateVector(Vect4);
    InitVector(&Vect4, M_MAX + 1, &error, &errorType);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    /* SetVectorElement() function test (test passed successfully). */
    printf("SetVectorElement() function test.\n\n");
    const uint8_t row = 0;

    printf("Test 5 - No error.\n");
    Vector Vect5 = InitVector(NULL, rows, &error, &errorType);
    error = SetVectorElement(&Vect5, row, value, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    // Deliberately generate error (The pointer is null).
    printf("Test 6 - The pointer is null.\n");
    Vector *Vect6 = NULL;
    error = SetVectorElement(Vect6, row, value, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    // Deliberately generate error (The vector is not initialized).
    printf("Test 7 - The vector is not initialized.\n");
    Vector Vect7;
    error = SetVectorElement(&Vect7, row, value, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    // Deliberately generate error (The row does not exist).
    printf("Test 8 - The row does not exist.\n");
    Vector Vect8 = InitVector(NULL, rows, &error, &errorType);
    error = SetVectorElement(&Vect8, M_MAX + 1, value, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    // Deliberately generate error (The value is not valid).
    printf("Test 9 - The value is not valid.\n");
    Vector Vect9 = InitVector(NULL, rows, &error, &errorType);
    error = SetVectorElement(&Vect9, row, NAN, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    // Deliberately generate error (The value is not valid).
    printf("Test 10 - The value is not valid.\n");
    Vector Vect10 = InitVector(NULL, rows, &error, &errorType);
    error = SetVectorElement(&Vect10, row, NAN, &errorType, NO_ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    /* GetVectorElement() function test (test passed successfully). */

    printf("GetVectorElement() function test.\n\n");
    printf("Test 11 - Not error.\n");
    Vector Vect11 = InitVector(NULL, rows, &error, &errorType);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n", ErrorTypeToString(errorType));
    printf("%f\n\n", value);

    // Deliberately generate error (The pointer is null).
    printf("Test 12 - The pointer is null.\n");
    Vector *Vect12 = NULL;
    value = GetVectorElement(Vect12, row, &error, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n", ErrorTypeToString(errorType));
    printf("%f\n\n", value);
    value = 1.0f;

    // Deliberately generate error (The vector is not initialized).
    printf("Test 13 - The vector is not initialized.\n");
    Vector Vect13;
    value = GetVectorElement(&Vect13, row, &error, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n", ErrorTypeToString(errorType));
    printf("%f\n\n", value);
    value = 1.0f;

    // Deliberately generate error (The row does not exist).
    printf("Test 14 - The row does not exist.\n");
    Vector Vect14 = InitVector(NULL, rows, &error, &errorType);
    value = GetVectorElement(&Vect14, M_MAX + 1, &error, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n", ErrorTypeToString(errorType));
    printf("%f\n\n", value);
    value = 1.0f;

    // Deliberately generate error (The value of the element is not valid).
    printf("Test 15 - The value of the element is not valid.\n");
    Vector Vect15 = InitVector(NULL, rows, &error, &errorType);
    Vect15.elements[row] = NAN; // Never do that!
    value = GetVectorElement(&Vect15, row, &error, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n", ErrorTypeToString(errorType));
    printf("%f\n\n", value);
    value = 1.0f;

    // Deliberately generate error (The value of the element is not valid).
    printf("Test 16 - The value of the element is not valid.\n");
    Vector Vect16 = InitVector(NULL, rows, &error, &errorType);
    Vect16.elements[row] = NAN; // Never do that!
    value = GetVectorElement(&Vect16, row, &error, &errorType, NO_ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n", ErrorTypeToString(errorType));
    printf("%f\n\n", value);
    value = 1.0f;

    /* FillVector() function test (test passed successfully). */

    printf("FillVector() function test.\n\n");
    printf("Test 17 - Not error.\n");
    Vector Vect17 = InitVector(NULL, rows, &error, &errorType);
    error = FillVector(&Vect17, value, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    // Deliberately generate error (The pointer is null).
    printf("Test 18 - The pointer is null.\n");
    Vector *Vect18 = NULL;
    error = FillVector(Vect18, value, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    // Deliberately generate error (The vector is not initialized).
    printf("Test 19 - The vector is not initialized.\n");
    Vector Vect19;
    error = FillVector(&Vect19, value, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    // Deliberately generate error (The number of rows exceeds M_MAX).
    printf("Test 20 - The number of rows exceeds M_MAX.\n");
    Vector Vect20 = InitVector(NULL, rows, &error, &errorType);
    Vect20.rows = M_MAX + 1;    // Never do that!
    error = FillVector(&Vect20, value, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    // Deliberately generate error (The value is not valid).
    printf("Test 21 - The value is not valid.\n");
    Vector Vect21 = InitVector(NULL, rows, &error, &errorType);
    error = FillVector(&Vect21, NAN, &errorType, ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    // Deliberately generate error (The value is not valid).
    printf("Test 22 - The value is not valid.\n");
    Vector Vect22 = InitVector(NULL, rows, &error, &errorType);
    error = FillVector(&Vect22, NAN, &errorType, NO_ROUTINE_CHECK);
    printf("Error status: ");
    PrintfBool(error);
    printf("Error type: %s\n\n", ErrorTypeToString(errorType));

    /* CopyVector() function test. */
    printf("CopyVector() function test.\n\n");
    printf("Test 23 - No error.\n");
    Vector Vect23 = InitVector(NULL, rows, &error, &errorType);
    Vector Vect23_ = InitVector(NULL, rows, &error, &errorType);
    error = FillVector(&Vect23, value, &errorType, NO_ROUTINE_CHECK);
    error =  PrintVector(&Vect23, &errorType, ROUTINE_CHECK);
    error =  PrintVector(&Vect23_, &errorType, ROUTINE_CHECK);
    error = CopyVector(&Vect23, &Vect23_, &errorType, ROUTINE_CHECK);
    error =  PrintVector(&Vect23, &errorType, ROUTINE_CHECK);
    error =  PrintVector(&Vect23_, &errorType, ROUTINE_CHECK);

    printf("\n");

    /* PrintVector() function test. */
    /*
    printf("PrintVector() function test.\n");
    Vector Vect24 = InitVector(NULL, rows, &error, &errorType);
    error =  PrintVector(&Vect24, &errorType, ROUTINE_CHECK);
    PrintfBool(error);
    printf("\n");
    */

    // Some code here.

    return error;
}
