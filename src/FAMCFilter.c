/***********************************************************
* OpenAHRS                                                 *
* $ Id: FAMCFilter.c v1.0 23/11/2023 22:25 t.borensztejn $ *
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

#include "../includes/FAMCFilter.h"

void UpdateFAMCFilter(const AccelerometerRawMeasurements* Acc, const MagnetometerRawMeasurements* Mag, float Quat[4]) {
    // Get the raw measurement values from 3-axis accelerometer.
    float ax = Acc->ax;
    float ay = Acc->ay;
    float az = Acc->az;

    // Get the raw measurement values from 3-axis magnetometer.
    float mx = Mag->mx;
    float my = Mag->my;
    float mz = Mag->mz;

    // Declare a 3D vector of raw accelerometer measurements.
    float acc[3];                   // Raw measurements vector in body frame.
    Init3DVector(acc, ax, ay, az);  // Store raw measurements into the vector.
    Normalize3DVector(acc);         // Normalize the vector (eq. 10).

    // Declare a 3D vector of raw magnetometer measurements.
    float mag[3];                   // Raw measurements vector in body frame.
    Init3DVector(mag, mx, my, mz);  // Store raw measurements into the vector.
    Normalize3DVector(mag);         // Normalize the vector (eq. 10).

    // Declare dynamic magnetometer reference vector.
    float mD = DotProduct(acc, mag, 3); // Check eq. 13.
    float mN = sqrt(1.0f - mD * mD);

    // Parameters of B matrix (eq. 18).
    float MatB[9];          // Declare the B matrix.
    InitMatrix(MatB, 3, 3); // Initialize the B matrix.

    SetElement(MatB, 3, 3, 0, 0, mN * mx);  // B11.
    SetElement(MatB, 3, 3, 1, 0, mN * my);  // B21.
    SetElement(MatB, 3, 3, 2, 0, mN * mz);  // B31.

    SetElement(MatB, 3, 3, 0, 0, mD * mx + ax);  // B13.
    SetElement(MatB, 3, 3, 1, 0, mD * my + ay);  // B23.
    SetElement(MatB, 3, 3, 2, 0, mD * mz + az);  // B33.

    MultiplyScalar(MatB, 3, 3, 0.5f);

    float tau = GetElement(MatB, 3, 3, 0, 2) + GetElement(MatB, 3, 3, 2, 0);
}
