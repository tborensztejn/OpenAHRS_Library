/******************************************************
* OpenAHRS                                            *
* $ Id: Utils.c v1.0 21/11/2023 23:00 t.borensztejn $ *
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

#include "../includes/Utils.h"

// Add an example here.
float Pow(const float x, const int8_t n) {
    float ret = 1.0f;   // Initialize the result to 1.0.

    // Determine the absolute value of the exponent.
    int8_t abs_n = abs(n);

    // Multiply the base value by itself for the absolute value of the exponent.
    for (int8_t i = 0; i < abs_n; i++) {
        ret *= x;
    }

    // If the original exponent was negative, take the reciprocal of the result.
    if (n < 0) {
        ret = 1.0f / ret;
    }

    return ret; // Return the calculated result.
}

// Add an example here.
unsigned long long int Factorial(const uint8_t n) {
    unsigned long long int ret; // Initialize the result variable.

    // Check for base cases: factorial of 0 and 1 is 1.
    if (n == 0 || n == 1) {
        // The factorial of 0 and 1 is 1.
        ret = 1;
    } else {
        // Recursive call to calculate the factorial for n greater than 1.
        ret = n * Factorial(n - 1);
    }

    return ret; // Return the calculated factorial.
}

// Add an example here.
int8_t Sign(const float x) {
    int8_t ret = -1;    // Initialize the result to -1.

    // If the input value is non-negative, set the result to 1.
    if (x >= 0.0f) {
        ret = 1;
    }

    return ret; // Return the determined sign.
}

// Add an example here.
float Min(const float x, const float y) {
    float ret = y;  // Initialize the result to the larger of the two numbers.

    // If x is smaller than y, update the result to x.
    if (x < y) {
        ret = x;
    }

    return ret; // Return the minimum value.
}

// Add an example here.
float Max(const float x, const float y) {
    float ret = y;  // Initialize the result to the smaller of the two numbers.

    // If x is greater than y, update the result to x.
    if (x > y) {
        ret = x;
    }

    return ret; // Return the maximum value.
}

// Add an example here.
float Degrees(const float angleRad) {
    float ret = angleRad * 180.0f / M_PI;   // Calculate the angle in degrees using the conversion factor.

	return ret;    // Return the angle in degrees.
}

// Add an example here.
float Radians(const float angleDegrees) {
    float ret = angleDegrees * M_PI / 180.0f;   // Calculate the angle in radians using the conversion factor.

	return ret;    // Return the angle in radians.
}

// Add an example here.
bool CloseAll(const float x, const float y, const float deviation) {
    bool ret = true;    // Initialize the result to true.

     // If the absolute difference between x and y is greater than the deviation, set the result to false.
    if (fabsf(x - y) > deviation) {
        ret = false;
    }

    return ret; // Return the result indicating whether the values are close.
}

// Add an example here.
uint8_t Argmax(const float *const tab, size_t len) {
    uint8_t index = 0;  // Initialize the index to the first element.

    // Iterate through the array, updating the index when a higher value is encountered.
    for (uint8_t n = 1; n < (uint8_t)len; n++) {
        if (tab[n] > tab[index]) {
            index = n;
        }
    }

    return index;   // Return the index of the maximum value.
}


uint8_t Argmin(const float *const tab, size_t len) {
    uint8_t index = 0;  // Initialize the index to the first element.

    // Iterate through the array, updating the index when a lower value is encountered.
    for (uint8_t n = 1; n < (uint8_t)len; n++) {
        if (tab[n] < tab[index]) {
            index = n;
        }
    }

    return index;   // Return the index of the minimum value.
}

// Add an example here.
float InvSqrt(float x) {
    // Fast inverse sqrt function.
    /*
     float halfx = 0.5f * x;
     float y = x;
     long i = *(long*)&y;
     i = 0x5f3759df - (i>>1);
     y = *(float*)&i;
     y = y * (1.5f - (halfx * y * y));
     y = y * (1.5f - (halfx * y * y));

     return y;
     */

     // Alternate form.
     unsigned int i = 0x5F1F1412 - (*(unsigned int*)&x >> 1);
     float tmp = *(float*)&i;
     float y = tmp * (1.69000231f - 0.714158168f * x * tmp * tmp);

     return y;
}

float Sat(const float x, const float min, const float max) {
    float ret = x;

    if (x < min) {
        ret = min;
    } else if (x > max) {
        ret = max;
    }

    return ret;
}
