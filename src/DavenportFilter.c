/**********************************************************
* OpenAHRS                                                *
* $ Id: Davenport.c v1.0 22/11/2023 23:00 t.borensztejn $ *
***********************************************************/

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

#include "../includes/DavenportFilter.h"

void UpdateDavenportQMethodFilter(
    AccelerometerRawMeasurements* Acc, MagnetometerRawMeasurements* Mag,
    float Quat[4], float PreviousQuat[4], float Ts,
    float w1, float w2, float g, float mdip) {

	float MatB[9];
	float MatB1[9];
	float MatB2[9];
	float _MatB[9];
	float MatS[9];
	float MatK[16];
	float MatSigma[9];
	float _MatK[9];
	float m_q[3];
	float g_q[3];
	float acc[3];
	float mag[3];
	float z[3];

    // Initialize vectors and matrices.
	//InitMatrix(MatB, 3, 3);
	//InitMatrix(MatB1, 3, 3);
	//InitMatrix(MatB2, 3, 3);
	//InitMatrix(_MatB, 3, 3);
	//InitMatrix(MatS, 3, 3);
	InitMatrix(MatK, 4, 4);
	Init3DVector(g_q, 0.0f, 0.0f, -g);
	Init3DVector(m_q, cos(mdip), 0.0f, -sin(mdip));

	float ax = Acc->ax;
	float ay = Acc->ay;
	float az = Acc->az;

	float mx = Mag->mx;
	float my = Mag->my;
	float mz = Mag->mz;

    Init3DVector(acc, ax, ay, az);
	Init3DVector(mag, mx, my, mz);
	OuterProduct(acc, g_q, MatB1, 3);
	OuterProduct(mag, m_q, MatB2, 3);
	MultiplyScalar(MatB1, 3, 3, w1);
	MultiplyScalar(MatB2, 3, 3, w2);
	Add(MatB1, MatB2, MatB, 3, 3);

	float sigma = Trace(MatB, 3, 3);
	float z1 = GetElement(MatB, 3, 3, 1, 2) - GetElement(MatB, 3, 3, 2, 1);
	float z2 = GetElement(MatB, 3, 3, 2, 0) - GetElement(MatB, 3, 3, 0, 2);
	float z3 = GetElement(MatB, 3, 3, 0, 1) - GetElement(MatB, 3, 3, 1, 0);

	Init3DVector(z, -z1, -z2, -z3);
	CopyMatrix(MatB, _MatB, 3, 3);
	Transpose(_MatB, 3, 3);
	Add(MatB, _MatB, MatS, 3, 3);
	SetElement(MatK, 4, 4, 0, 0, sigma);
	InitIdentityMatrix(MatSigma, 3);
	MultiplyScalar(MatSigma, 3, 3, sigma);
	Subtract(MatS, MatSigma, _MatK, 3, 3);

	for (uint8_t row = 1; row < 4; row++) {
		float element = GetElement(z, 3, 1, row-1, 0);
		SetElement(MatK, 4, 4, row, 0, element);
		SetElement(MatK, 4, 4, 0, row, element);

		for (uint8_t column = 1; column < 4; column++) {
			element = GetElement(_MatK, 3, 3, row-1, column-1);
			SetElement(MatK, 4, 4, row, column, element);
		}
	}

	//PrintMatrix(MatK, 4, 4);

    // Compute eigenvalues and eigenvectors of K matrix.
	float eigenValues[4];
    float eigenVectors[16];
    bool isConverging = Eigen(MatK, 4, eigenValues, eigenVectors, 10000, true);
	//PrintMatrix(eigenValues, 4, 1);
    //PrintMatrix(eigenVectors, 4, 4);
    //uint8_t index = Argmax(eigenValues, sizeof(eigenValues) / sizeof(float));
    uint8_t index = Argmax(eigenValues, 4);

    // Extract quaternion components from the selected eigenvector.
    float qw = GetElement(eigenVectors, 4, 4, 0, index);
    float qx = GetElement(eigenVectors, 4, 4, 1, index);
    float qy = GetElement(eigenVectors, 4, 4, 2, index);
    float qz = GetElement(eigenVectors, 4, 4, 3, index);

    InitQuaternion(Quat, qw, qx, qy, qz);   // Update quaternion.

    //printf("%d\n", isConverging);
}
