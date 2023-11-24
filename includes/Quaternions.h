/************************************************************
* OpenAHRS                                                  *
* $ Id: Quaternions.h v1.0 22/11/2023 10:40 t.borensztejn $ *
*************************************************************/

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

#ifndef QUATERNIONS_H
#define QUATERNIONS_H

#include "Linalg.h"

/*** Declaration of structures. ***/

typedef struct {
    float phi;         // Roll angle (X axis).
    float theta;       // Pitch angle (Y axis).
    float psi;         // Yaw angle (Z axis).
} TaitBryanAngles;

/*** Declaration of function prototypes for quaternion manipulation. ***/

// This function is used to initialize a quaternion with the specified quaternion components (qw, qx, qy, qz).
void InitQuaternion(float Quat[4], const float qw, const float qx, const float qy, const float qz);
// This function is used to compute the conjugate of a quaternion.
void Conjugate(float Quat[4]);
// This function ise used to compute the conjugate of a quaternion while preserving the original quaternion.
void Conugate2(const float Quat[4], float ConjQuat[4]);
// This function is used to normalize a quaternion.
void NormalizeQuaternion(float Quat[4]);
// This function is used to normalize a quaternion while preserving the original quaternion.
void NormalizeQuaternion2(const float Quat[4], float NormalizedQuat[4]);
// This function is used to multiply two quaternions.
void MultiplyQuat(const float QuatA[4], const float QuatB[4], float QuatC[4]);
// This function is used to convert a quaternion to a 3x3 rotation matrix.
void QuaternionToRotMatrix(const float Quat[4], float MatRot[9]);
// This function is used to convert a quaternion to a Direction Cosine Matrix (DCM).
void QuaternionToDCM(const float Quat[4], float dcm[9]);
// This function is used to convert a quaternion  to Tait-Bryan angles (pitch, roll, and yaw).
void QuaternionToTaitBryanAngles(const float Quat[4], TaitBryanAngles *Angles);

#endif
