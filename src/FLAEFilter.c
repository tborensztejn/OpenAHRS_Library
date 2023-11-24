/***********************************************************
* OpenAHRS                                                 *
* $ Id: FLAEFilter.c v1.0 24/11/2023 22:25 t.borensztejn $ *
************************************************************/

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

#include "../includes/FLAEFilter.h"

void UpdateFLAEFilter(
    const AccelerometerRawMeasurements* Acc, const MagnetometerRawMeasurements* Mag, float Quat[4],
    const uint8_t method, const float w1, const float w2, const float mdip) {
        float accRg[3];                         // Declare the vector containing the acceleration components measured in the fixed Galilean reference frame.
        Init3DVector(accRg, 0.0f, 0.0f, -1.0f); // Initialize this vector accRg = trans([0 0 -g]) and after normalization, accRg = trans([0 0 -1]).

        // Get the raw measurement values from 3-axis accelerometer.
        float acc[3];                                   // Declare the vector of raw acceleration measurements, which includes acceleration components measured in the sensor frame.
        Init3DVector(acc, Acc->ax, Acc->ay, Acc->az);    // Initialize the vector with raw measurements.
}
