/******************************************************
* OpenAHRS                                            *
* $ Id: Utils.h v1.0 21/11/2023 23:00 t.borensztejn $ *
******************************************************/

/*
    MIT License.
    Copyright 2023 Titouan Borensztejn <borensztejn.titouan@gmail.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software
    and associated documentation files (the "Software"), to deal in the Software without restriction,
    including without limitation the rights to use, copy, modify, merge, publish, distribute,
    sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or
    substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
    BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
    DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>      // This includes declarations and definitions necessary for standard input/output operations in C.
#include <stdlib.h>     // This includes declarations for functions related to dynamic memory management.
#include <stdint.h>     // This includes definitions for standard integer types with specified widths.
#include <stddef.h>     // This includes definitions related to pointer management.
#include <math.h>       // This includes declarations for standard mathematical functions in C.
#include <stdbool.h>    // This includes the necessary declarations to use the boolean data type and related constants (true and false).

#define EPSILON 0.000000001f

/*** Declaration of useful function prototypes. ***/

// This function is used to calculate the power of a given float value (x) raised to the exponent of an 8-bit integer (n).
float Pow(const float x, const int8_t n);
// This function is used to calculate the factorial of a given unsigned 8-bit integer (n).
unsigned long long int Factorial(const uint8_t n);
// This function is used to determine the sign of a given float value (x).
int8_t Sign(const float x);
// This function is used to find the minimum value between two float numbers (x and y).
float Min(const float x, const float y);
// This function is used to find the maximum value between two float numbers (x and y).
float Max(const float x, const float y);
// This function is used to convert an angle in radians to degrees.
float Degrees(const float angleRad);
// This function is used to convert an angle in degrees to radians.
float Radians(const float angleDegrees);
// This function is used to check if two float values (x and y) are close to each other within a specified deviation.
bool CloseAll(const float x, const float y, const float deviation);
// This function is used to find the index of the maximum value in an array of float values (tab) of a given length (len).
uint8_t Argmax(const float *const tab, size_t len);
// This function is used to find the index of the minimum value in an array of float values (tab) of a given length (len).
uint8_t Argmin(const float *const tab, size_t len);
// This function is used to calculate the inverse of the sqrt function.
float InvSqrt(float x);

#endif
