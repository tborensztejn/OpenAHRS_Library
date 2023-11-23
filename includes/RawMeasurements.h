/****************************************************************
* OpenAHRS                                                      *
* $ Id: RawMeasurements.h v1.0 22/11/2023 10:10 t.borensztejn $ *
*****************************************************************/

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

#ifndef RAW_MEASUREMENTS_H
#define RAW_MEASUREMENTS_H

// Structure representing raw gyroscope measurements in sensor frame.
typedef struct {
	float p;   // Angular rate around the X-axis (rad/s).
	float q;   // Angular rate around the Y-axis (rad/s).
	float r;   // Angular rate around the Z-axis (rad/s).
} GyroscopeRawMeasurements;

// Structure representing raw accelerometer measurements in sensor frame.
typedef struct {
    float ax;   // Acceleration along the X-axis (m/s²).
    float ay;   // Acceleration along the Y-axis (m/s²).
    float az;   // Acceleration along the Z-axis (m/s²).
} AccelerometerRawMeasurements;

// Structure representing raw magnetometer measurements in sensor frame.
typedef struct {
    float mx;   // Magnetic field strength along the X-axis (µT).
    float my;   // Magnetic field strength along the Y-axis (µT).
    float mz;   // Magnetic field strength along the Z-axis (µT).
} MagnetometerRawMeasurements;

#endif
