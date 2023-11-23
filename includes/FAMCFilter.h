/***********************************************************
* OpenAHRS                                                 *
* $ Id: FAMCFilter.h v1.0 23/11/2023 22:25 t.borensztejn $ *
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

    .. [Liu] Zhuohua Liu, Wei Liu, Xiangyang Gong, and Jin Wu, "Simplified Attitude
    Determination Algorithm Using Accelerometer and Magnetometer with Extremely
    Low Execution Time," Journal of Sensors, vol. 2018, Article ID 8787236, 11
    pages, 2018. https://doi.org/10.1155/2018/8787236.
*/

#ifndef FAMC_FILTER_H
#define FAMC_FILTER_H

#include "Quaternions.h"
#include "RawMeasurements.h"

/*
    Sensors required for operation:

    3-axis accelerometer:   Required.
    3-axis gyrometer:       Optional (Not implemented).
    3-axis magnetometer:    Required.

    Note: this data fusion algorithm can only work if the following sensor associations are met.
    Accelerometer + Magnetometer: OK.
*/

/*** Declaration of function prototype(s). ***/

void UpdateFAMCFilter(const AccelerometerRawMeasurements* Acc, const MagnetometerRawMeasurements* Mag, float Quat[4]);

#endif
