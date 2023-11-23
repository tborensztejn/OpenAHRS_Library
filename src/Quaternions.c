/************************************************************
* OpenAHRS                                                  *
* $ Id: Quaternions.c v1.0 22/11/2023 10:40 t.borensztejn $ *
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

#include "../includes/Quaternions.h"


/*** Declaration of functions for quaternion manipulation. ***/

// Add an example here.
void InitQuaternion(float Quat[4], const float qw, const float qx, const float qy, const float qz) {
    // A quaternion is a matrix of size (4x1) and therefore also a 4D vector.
    Init4DVector(Quat, qw, qx, qy, qz); // Use the Init4DVector function to set the quaternion elements.
}

// Add an example here.
void Conjugate(float Quat[4]) {
    // Extract components of the quaternion.
    float qw = GetElement(Quat, 4, 1, 0, 0);
    float qx = GetElement(Quat, 4, 1, 1, 0);
    float qy = GetElement(Quat, 4, 1, 2, 0);
    float qz = GetElement(Quat, 4, 1, 3, 0);

    Init4DVector(Quat, qw, -qx, -qy, -qz);  // Use the Init4DVector function to set the conjugate quaternion elements.
}

// Add an example here.
void Conjugate2(const float Quat[4], float ConjQuat[4]) {
    // Extract components of the input quaternion.
    float qw = GetElement(Quat, 4, 1, 0, 0);
    float qx = GetElement(Quat, 4, 1, 1, 0);
    float qy = GetElement(Quat, 4, 1, 2, 0);
    float qz = GetElement(Quat, 4, 1, 3, 0);

    Init4DVector(ConjQuat, qw, -qx, -qy, -qz);  // Use the Init4DVector function to set the conjugate quaternion elements.
}

// Add an example here.
void NormalizeQuaternion(float Quat[4]) {
    NormalizeVector(Quat, 4);
}

// Add an example here.
void NormalizeQuaternion2(const float Quat[4], float NormalizedQuat[4]) {
    NormalizeVector2(Quat, NormalizedQuat, 4);
}

// Add an example here.
void MultiplyQuat(const float QuatA[4], const float QuatB[4], float QuatC[4]) {
    // Extract components of the first quaternion (QuatA).
	float qwa = GetElement(QuatA, 4, 1, 0, 0);
	float qxa = GetElement(QuatA, 4, 1, 1, 0);
	float qya = GetElement(QuatA, 4, 1, 2, 0);
	float qza = GetElement(QuatA, 4, 1, 3, 0);

    // Extract components of the second quaternion (QuatB).
	float qwb = GetElement(QuatB, 4, 1, 0, 0);
    float qxb = GetElement(QuatB, 4, 1, 1, 0);
    float qyb = GetElement(QuatB, 4, 1, 2, 0);
    float qzb = GetElement(QuatB, 4, 1, 3, 0);

    // Calculate the components of the resulting quaternion (QuatC).
	float qw = qwa * qwb - qxa * qxb - qya * qyb - qza * qzb;
	float qx = qwa * qxb + qxa * qwb - qza * qyb + qya * qzb;
	float qy = qwa * qyb + qza * qxb + qwb * qya - qxa * qzb;
	float qz = qwa * qzb - qya * qxb + qxa * qyb + qwb * qza;

    // Store the components of the resulting quaternion in the third quaternion (QuatC).
	SetElement(QuatC, 4, 1, 0, 0, qw);
    SetElement(QuatC, 4, 1, 1, 0, qx);
    SetElement(QuatC, 4, 1, 2, 0, qy);
    SetElement(QuatC, 4, 1, 3, 0, qz);
}

// Add an example here.
void QuaternionToRotMatrix(const float Quat[4], float MatRot[9]) {
	float CopiedQuat[4];
	float element = 0.0f;

	// Make a copy of the quaternion to avoid modifying the original.
	CopyMatrix(Quat, CopiedQuat, 4, 1);
	// Normalise the quaternion.
	NormalizeQuaternion(CopiedQuat);
	//InitMatrix(MatRot, 3, 3);

	float qw = GetElement(CopiedQuat, 4, 1, 0, 0);
	float qx = GetElement(CopiedQuat, 4, 1, 1, 0);
	float qy = GetElement(CopiedQuat, 4, 1, 2, 0);
	float qz = GetElement(CopiedQuat, 4, 1, 3, 0);

	element = 1.0f - 2.0f * (qy * qy + qz * qz);
	SetElement(MatRot, 3, 3, 0, 0, element);
	element = 2.0f * (qx * qy - qw * qz);
	SetElement(MatRot, 3, 3, 0, 1, element);
	element = 2.0f * (qx * qz + qw * qy);
	SetElement(MatRot, 3, 3, 0, 2, element);

	element = 2.0f * (qx * qy + qw * qz);
	SetElement(MatRot, 3, 3, 1, 0, element);
	element = 1.0f - 2.0f * (qx * qx + qz * qz);
	SetElement(MatRot, 3, 3, 1, 1, element);
	element = 2.0f * (qy * qz - qw * qx);
	SetElement(MatRot, 3, 3, 1, 2, element);

	element = 2.0f * (qx * qz - qw * qy);
	SetElement(MatRot, 3, 3, 2, 0, element);
	element = 2.0f * (qw * qx + qy * qz);
	SetElement(MatRot, 3, 3, 2, 1, element);
	element = 1.0f - 2.0f * (qx * qx + qy * qy);
	SetElement(MatRot, 3, 3, 2, 2, element);
}

// Add an example here.
void QuaternionToDCM(const float Quat[4], float dcm[9]) {
	float CopiedQuat[4];
	float element = 0.0f;

	// Make a copy of the quaternion to avoid modifying the original.
	CopyMatrix(Quat, CopiedQuat, 4, 1);
	// Normalise the quaternion.
	NormalizeQuaternion(CopiedQuat);
	//InitMatrix(dcm, 3, 3);

	float qw = GetElement(CopiedQuat, 4, 1, 0, 0);
	float qx = GetElement(CopiedQuat, 4, 1, 1, 0);
	float qy = GetElement(CopiedQuat, 4, 1, 2, 0);
	float qz = GetElement(CopiedQuat, 4, 1, 3, 0);

	element = qw * qw + qx * qx - qy * qy - qz * qz;
	SetElement(dcm, 3, 3, 0, 0, element);
	element = 2.0f * (qx * qy - qw * qz);
	SetElement(dcm, 3, 3, 0, 1, element);
	element = 2.0f * (qx * qz + qw * qy);
	SetElement(dcm, 3, 3, 0, 2, element);

	element = 2.0f * (qx * qy + qw * qz);
	SetElement(dcm, 3, 3, 1, 0, element);
	element = qw * qw - qx * qx + qy * qy - qz * qz;
	SetElement(dcm, 3, 3, 1, 1, element);
	element = 2.0f * (qy * qz - qw * qx);
	SetElement(dcm, 3, 3, 1, 2, element);

	element = 2.0f * (qx * qz - qw * qy);
	SetElement(dcm, 3, 3, 2, 0, element);
	element = 2.0f * (qy * qz + qw * qx);
	SetElement(dcm, 3, 3, 2, 1, element);
	element = qw * qw - qx * qx - qy * qy + qz * qz;
	SetElement(dcm, 3, 3, 2, 2, element);
}

void QuaternionToTaitBryanAngles(const float Quat[4], TaitBryanAngles *Angles) {
	float qw = GetElement(Quat, 4, 1, 0, 0);
	float qx = GetElement(Quat, 4, 1, 1, 0);
	float qy = GetElement(Quat, 4, 1, 2, 0);
	float qz = GetElement(Quat, 4, 1, 3, 0);

	// Roll (rotation about the X axis).
	float sinr_cost = 2.0f * (qw * qx + qy * qz);
	float cosr_cost = 1.0f - 2.0f * (qx * qx + qy * qy);

	Angles->phi = atan2(sinr_cost, cosr_cost);

	// Pitch (rotation about the Y axis).
	double sint = sqrt(1.0f + 2.0f * (qw * qy - qx * qz));
	double cost = sqrt(1.0f - 2.0f * (qw * qy - qx * qz));
	Angles->theta = 2.0f * atan2(sint, cost) - M_PI / 2.0f;

	// Yaw (rotation about the Z axis).
	float sinl_cost = 2.0f * (qw * qz + qx * qy);
	float cosl_cost = 1.0f - 2.0f * (qy * qy + qz * qz);
	Angles->psi = atan2(sinl_cost, cosl_cost);
}
