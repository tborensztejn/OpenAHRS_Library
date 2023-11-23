/***********************************************************
* OpenAHRS                                                 *
* $ Id: AQUAFilter.h v1.0 23/11/2023 00:15 t.borensztejn $ *
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

/*
    References:

    .. [Valenti2015] Valenti, R.G.; Dryanovski, I.; Xiao, J. Keeping a Good
    Attitude: A Quaternion-Based Orientation Filter for IMUs and MARGs. Sensors
    2015, 15, 19302-19330.
    (https://res.mdpi.com/sensors/sensors-15-19302/article_deploy/sensors-15-19302.pdf)

    .. [Valenti2016] R. G. Valenti, I. Dryanovski and J. Xiao, "A Linear Kalman
    Filter for MARG Orientation Estimation Using the Algebraic Quaternion
    Algorithm," in IEEE Transactions on Instrumentation and Measurement, vol.
    65, no. 2, pp. 467-481, 2016.
    (https://ieeexplore.ieee.org/document/7345567)
*/

#ifndef AQUA_FILTER_H
#define AQUA_FILTER_H

#include "Quaternions.h"
#include "RawMeasurements.h"

/*
    Sensors required for operation:

    3-axis accelerometer:   Required.
    3-axis gyrometer:       Optional.
    3-axis magnetometer:	Required.

    Note: this data fusion algorithm can only work if the following sensor associations are met.
    Accelerometer + Magnetometer: OK.
    Accelerometer + Magnetometer + Gyrometer: OK.
*/

/*** Declaration of function prototype(s). ***/

void Slerp(float Quat[4], const float alpha, const float treshold, float InterpolatedQuat[4]);
float AdaptiveGain(const float gain, const float Vect[3], const float firstTreshold, const float secondTreshold, const float magnitude);
void OmegaMatrix(const float gyr[3], float MatOmega[16]);

void UpdateAQUAFilter(
	const AccelerometerRawMeasurements* Acc, const GyroscopeRawMeasurements* Gyr, const MagnetometerRawMeasurements* Mag,
	float Quat[4], float PreviousQuat[4], const float Ts,
	const bool adaptive, const float alpha, float *previousAlpha, const float beta, float *previousBeta, const float adaptiveGainFirstThreshold, const float adaptiveGainSecondThreshold, const float accelerometerSlerpTreshold, const float magnetometerSlerpTreshold, const float g, const float h);

#endif
