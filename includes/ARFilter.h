/*********************************************************
* OpenAHRS                                               *
* $ Id: ARFilter.h v1.0 22/11/2023 11:45 t.borensztejn $ *
*********************************************************/

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

    .. [Jia] Yan-Bin Jia. Quaternions. 2018.
    (http://web.cs.iastate.edu/~cs577/handouts/quaternion.pdf)

    .. [Sola] Solà, Joan. Quaternion kinematics for the error-state Kalman Filter.
    October 12, 2017.
    (http://www.iri.upc.edu/people/jsola/JoanSola/objectes/notes/kinematics.pdf)

    .. [Zhao] F. Zhao and B.G.M. van Wachem. A novel Quaternion integration
    approach for describing the behaviour of non-spherical particles.
    (https://link.springer.com/content/pdf/10.1007/s00707-013-0914-2.pdf)
*/

#ifndef AR_FILTER_H
#define AR_FILTER_H

#include "Quaternions.h"
#include "RawMeasurements.h"

#define CLOSED  1
#define SERIES	2

/*
    Sensors required for operation:

    3-axis accelerometer:   Not required (Can be used to initialise the initial quaternion. Not integrated with the AR filter).
    3-axis gyrometer:       Required.
    3-axis magnetometer:	Not required (Can be used to initialise the initial quaternion. Not integrated with AR filter).
*/

/*** Declaration of function prototype(s). ***/

void UpdateARFilter(const GyroscopeRawMeasurements* Gyr, float Quat[4], float PreviousQuat[4], const float Te, const uint8_t order, const uint8_t method);

#endif
