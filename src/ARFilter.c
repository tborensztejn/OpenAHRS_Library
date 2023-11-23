/*********************************************************
* OpenAHRS                                               *
* $ Id: ARFilter.c v1.0 22/11/2023 11:45 t.borensztejn $ *
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

#include "../includes/ARFilter.h"

/*** Declaration of function(s). ***/

void UpdateARFilter(const GyroscopeRawMeasurements* Gyr, float Quat[4], float PreviousQuat[4], const float Te, const uint8_t order, const uint8_t method) {
    float MatOmega[16];
    float MatA[16];
    float _MatA[16];
    float gyr[3];

    float qw;
    float qx;
    float qy;
    float qz;

    //InitMatrix(MatOmega, 4, 4);
    //InitMatrix(_MatA, 4, 4);
    InitIdentityMatrix(MatA, 4);
    Init3DVector(gyr, Gyr->p, Gyr->q, Gyr->r);

    float w = Norm3D(gyr);

    if (w > EPSILON) {
        float theta = w * Te / 2.0f;

        SetElement(MatOmega, 4, 4, 0, 0, 0.0f);
        SetElement(MatOmega, 4, 4, 1, 0, Gyr->p);
        SetElement(MatOmega, 4, 4, 2, 0, Gyr->q);
        SetElement(MatOmega, 4, 4, 3, 0, Gyr->r);

        SetElement(MatOmega, 4, 4, 0, 1, -Gyr->p);
        SetElement(MatOmega, 4, 4, 1, 1, 0.0f);
        SetElement(MatOmega, 4, 4, 2, 1, -Gyr->r);
        SetElement(MatOmega, 4, 4, 3, 1, Gyr->q);

        SetElement(MatOmega, 4, 4, 0, 2, -Gyr->q);
        SetElement(MatOmega, 4, 4, 1, 2, Gyr->r);
        SetElement(MatOmega, 4, 4, 2, 2, 0.0f);
        SetElement(MatOmega, 4, 4, 3, 2, -Gyr->p);

        SetElement(MatOmega, 4, 4, 0, 3, -Gyr->r);
        SetElement(MatOmega, 4, 4, 1, 3, -Gyr->q);
        SetElement(MatOmega, 4, 4, 2, 3, Gyr->p);
        SetElement(MatOmega, 4, 4, 3, 3, 0.0f);

        if (method == CLOSED) {
            MultiplyScalar(MatA, 4, 4, cos(theta));
            MultiplyScalar(MatOmega, 4, 4, sin(theta) / w);
            Add(MatA, MatOmega, _MatA, 4, 4);
        } else if (method == SERIES) {
            float MatS[16];

            for (uint8_t n = 1; n <= order; n++) {
                //InitMatrix(MatS, 4, 4);
                CopyMatrix(MatOmega, MatS, 4, 4);
                MultiplyScalar(MatS, 4, 4, 0.5f * Te);
                Power(MatS, 4, 4, n);
                unsigned long long int coef = Factorial(n);
                MultiplyScalar(MatS, 4, 4, 1.0f / (float)coef);
                Add(MatS, MatA, _MatA, 4, 4);
                CopyMatrix(_MatA, MatA, 4, 4);
            }
        } else {
            // Some code here.
        }

        Multiply(_MatA, 4, 4, PreviousQuat, 4, 1, Quat);
        NormalizeQuaternion(Quat);
    } else {
        qw = 1.0f;
        qx = 0.0f;
        qy = 0.0f;
        qz = 0.0f;

        InitQuaternion(Quat, qw, qx, qy, qz);
    }

    CopyMatrix(Quat, PreviousQuat, 4, 1);
}
