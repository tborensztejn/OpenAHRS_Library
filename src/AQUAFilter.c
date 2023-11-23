/***********************************************************
* OpenAHRS                                                 *
* $ Id: AQUAFilter.c v1.0 23/11/2023 00:15 t.borensztejn $ *
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

#include "../includes/AQUAFilter.h"

// Add an example here.
void Slerp(float Quat[4], const float alpha, const float treshold, float InterpolatedQuat[4]) {
    float CopiedQuat[4];
	float _InterpolatedQuat[4];

	//InitMatrix(CopiedQuat, 4, 1);
	//InitMatrix(_InterpolatedQuat, 4, 1);
	CopyMatrix(Quat, CopiedQuat, 4, 1);

	float qw = GetElement(Quat, 4, 1, 0, 0);

	InitQuaternion(InterpolatedQuat, 1.0f, 0.0f, 0.0f, 0.0f);

	if (qw > treshold) {
		// LERP algorithm.
		MultiplyScalar(InterpolatedQuat, 4, 1, 1.0f - alpha);
		MultiplyScalar(CopiedQuat, 4, 1, alpha);
		Add(InterpolatedQuat, CopiedQuat, _InterpolatedQuat, 4, 1);
		CopyMatrix(_InterpolatedQuat, InterpolatedQuat, 4, 1);
	} else {
		// SLERP algorithm.
		float angle = acos(qw);
		float gain = sin(fabs(1.0f - alpha) * angle) / sin(angle);
		MultiplyScalar(InterpolatedQuat, 4, 1, gain);
		gain = sin(alpha * angle) / sin(angle);
		MultiplyScalar(CopiedQuat, 4, 1, gain);
		Add(InterpolatedQuat, CopiedQuat, _InterpolatedQuat, 4, 1);
		CopyMatrix(_InterpolatedQuat, InterpolatedQuat, 4, 1);
	}

	NormalizeQuaternion(InterpolatedQuat);
}

// Add an example here.
float AdaptiveGain(const float gain, const float Vect[3], const float firstTreshold, const float secondTreshold, const float magnitude) {
	float ret = 0.0f;

    // The second treshold must be strictly greater than the first.
    if (firstTreshold < secondTreshold) {
        float factor = 0.0f;
		float norm = Norm3D(Vect);
		//float magnitudeError = fabs(norm - magnitude) / magnitude;
        float magnitudeError = fabsf(norm - fabsf(magnitude)) / fabsf(magnitude);

        // Check if magnitude error falls within the specified thresholds.
		if (firstTreshold < magnitudeError && magnitudeError < secondTreshold) {
			factor = (secondTreshold - magnitudeError) / firstTreshold;
		}

        // If magnitude error is below or equal to the first threshold, set factor to 1.0.
		if (magnitudeError <= firstTreshold) {
			factor = 1.0f;
		}

		ret = factor * gain;  // Calculate the final adaptive gain.
    }

	return ret;
}

// Add an example here.
void OmegaMatrix(const float gyr[3], float MatOmega[16]) {
    float p = GetElement(gyr, 3, 1, 0, 0);
    float q = GetElement(gyr, 3, 1, 1, 0);
    float r = GetElement(gyr, 3, 1, 2, 0);

    SetElement(MatOmega, 4, 4, 0, 0, 0.0f);
    SetElement(MatOmega, 4, 4, 0, 1, p);
    SetElement(MatOmega, 4, 4, 0, 2, q);
    SetElement(MatOmega, 4, 4, 0, 3, r);

    SetElement(MatOmega, 4, 4, 1, 0, -p);
    SetElement(MatOmega, 4, 4, 1, 1, 0.0f);
    SetElement(MatOmega, 4, 4, 1, 2, r);
    SetElement(MatOmega, 4, 4, 1, 3, -q);

    SetElement(MatOmega, 4, 4, 2, 0, -q);
    SetElement(MatOmega, 4, 4, 2, 1, -r);
    SetElement(MatOmega, 4, 4, 2, 2, 0.0f);
    SetElement(MatOmega, 4, 4, 2, 3, p);

    SetElement(MatOmega, 4, 4, 3, 0, -r);
    SetElement(MatOmega, 4, 4, 3, 1, q);
    SetElement(MatOmega, 4, 4, 3, 2, -p);
    SetElement(MatOmega, 4, 4, 3, 3, 0.0f);
}

// Add an example here.
void UpdateAQUAFilter(
	const AccelerometerRawMeasurements* Acc, const GyroscopeRawMeasurements* Gyr, const MagnetometerRawMeasurements* Mag,
	float Quat[4], float PreviousQuat[4], const float Ts,
	const bool adaptive, const float alpha, float *previousAlpha, const float beta, float *previousBeta, const float adaptiveGainFirstThreshold, const float adaptiveGainSecondThreshold, const float accelerometerSlerpTreshold, const float magnetometerSlerpTreshold, const float g, const float h) {

	float acc[3];
	float mag[3];
	float gyr[3];
	float qAcc[4];
	float qMag[4];
	float qGyr[4];

	Init3DVector(acc, Acc->ax, Acc->ay, Acc->az);
	Normalize3DVector(acc);
	Init3DVector(mag, Mag->mx, Mag->my, Mag->mz);
	Normalize3DVector(mag);
	Init3DVector(gyr, Gyr->p, Gyr->q, Gyr->r);

    // Flags to check if sensor measurements are valid.
	bool accOK = false;
	bool magOK = false;
	bool gyrOK = false;

	if (Norm3D(acc) > EPSILON) {
		accOK = true;
	}

	if (Norm3D(mag) > EPSILON) {
        magOK = true;
    }

	if (Norm3D(gyr) > EPSILON) {
        gyrOK = true;
    }

	/*
	printf("accOK: %d\n", accOK);
	printf("magOK: %d\n", magOK);
	printf("gyrOK: %d\n\n", gyrOK);
	*/

	float ax = GetElement(acc, 3, 1, 0, 0);
	float ay = GetElement(acc, 3, 1, 1, 0);
	float az = GetElement(acc, 3, 1, 2, 0);

	float mx = GetElement(mag, 3, 1, 0, 0);
	float my = GetElement(mag, 3, 1, 1, 0);
	float mz = GetElement(mag, 3, 1, 2, 0);

	float p = GetElement(gyr, 3, 1, 0, 0);
    float q = GetElement(gyr, 3, 1, 1, 0);
    float r = GetElement(gyr, 3, 1, 2, 0);

	if (accOK && magOK && gyrOK) {
		/* Prediction step. */
		float MatOmega[16];
		float DerivativeQuat[4];
		//float IntegratedQuat[4];

		//InitMatrix(MatOmega, 4, 4);
		//InitQuaternion(DerivativeQuat, 1.0f, 0.0f, 0.0f, 0.0f);
		//InitQuaternion(IntegratedQuat, 1.0f, 0.0f, 0.0f, 0.0f);
		OmegaMatrix(gyr, MatOmega);
		MultiplyScalar(MatOmega, 4, 4, -0.5f);
		Multiply(MatOmega, 4, 4, PreviousQuat, 4, 1, DerivativeQuat);
		MultiplyScalar(DerivativeQuat, 4, 1, Ts);
		//Add(Quaternion, DerivativeQuat, IntegratedQuat, 4, 1);
		//NormalizeQuaternion(IntegratedQuat);
		Add(PreviousQuat, DerivativeQuat, qGyr, 4, 1);
		NormalizeQuaternion(qGyr);

		/* Check whether it would not be more appropriate to use the AR filter to determine the quaternion with the 3-axis gyro.

		/* Accelerometer-based correction step. */
		float dcmRmRg[9];
		float accRg[3];

		//InitMatrix(dcmRmRg, 3, 3);
		//Init3DVector(accRg, 0.0f, 0.0f, 0.0f);
		QuaternionToDCM(qGyr, dcmRmRg);
		Transpose(dcmRmRg, 3, 3);
		Multiply(dcmRmRg, 3, 3, acc, 3, 1, accRg);

		float gx = GetElement(accRg, 3, 1, 0, 0);
		float gy = GetElement(accRg, 3, 1, 1, 0);
		float gz = GetElement(accRg, 3, 1, 2, 0);

		// Determine the quaternion (partial orientation) from the accelerometer measurements.
		//if (az >= 0.0f) {
		if (gz < 0.0f) {
			/*
			float qw = sqrt((az + 1.0f) / 2.0f);
			float qx = -ay / sqrt(2.0f * (1.0f - ax));
			float qy = ax / sqrt(2.0f * (az + 1.0f));
			float qz = 0.0f;
			*/

			float l1 = sqrt((1.0f - gz) / 2.0f);
			float qw = l1;
			float qx = gy / (2.0f * l1);
			float qy = -gx / (2.0f * l1);
			float qz = 0.0f;

			InitQuaternion(qAcc, qw, qx, qy, qz);
		} else {
			/*
			float qw = -ay / sqrt(2.0f * (1.0f - az));
			float qx = sqrt((1.0f - az) / 2.0f);
			float qy = 0.0f;
			float qz = ax / sqrt(2.0f * (1.0f - az));
			*/

			float l2 = sqrt((1.0f + gz) / 2.0f);
			float qw = gy / (2.0f * l2);
			float qx = l2;
			float qy = 0.0f;
			float qz = -gx / (2.0f * l2);

			InitQuaternion(qAcc, qw, qx, qy, qz);
		}

		// Check the parameters.
		float accFactor = alpha;

		if (adaptive) {
			accFactor = AdaptiveGain(*previousAlpha, accRg, adaptiveGainFirstThreshold, adaptiveGainSecondThreshold, g);
			*previousAlpha = accFactor;
		} else {
			*previousAlpha = alpha;
		}

		float _qAcc[4];
		float _Quat[4];
        //InitQuaternion(_qAcc, 1.0f, 0.0f, 0.0f, 0.0f);
		//InitQuaternion(_Quat, 1.0f, 0.0f, 0.0f, 0.0f);
		Slerp(qAcc, accFactor, accelerometerSlerpTreshold, _qAcc);
		MultiplyQuat(qGyr, _qAcc, _Quat);

		/* Magnetometer-based correction step. */
		float magRg[3];

		//InitMatrix(dcmRmRg, 3, 3);
		//Init3DVector(magRg, 0.0f, 0.0f, 0.0f);
		QuaternionToDCM(_Quat, dcmRmRg);
		Transpose(dcmRmRg, 3, 3);
		Multiply(dcmRmRg, 3, 3, mag, 3, 1, magRg);

		float lx = GetElement(magRg, 3, 1, 0, 0);
		float ly = GetElement(magRg, 3, 1, 1, 0);
		//float lz = GetElement(magRg, 3, 1, 2, 0);

		float gamma = lx * lx + ly * ly;

		if (lx >= 0.0f) {
			float qw = sqrt(gamma + lx * sqrt(gamma)) / sqrt(2.0f * gamma);
			float qx = 0.0f;
			float qy = 0.0f;
			float qz = ly / (sqrt(2.0f) * sqrt(gamma + lx * sqrt(gamma)));

			InitQuaternion(qMag, qw, qx, qy, qz);
		} else {
			float qw = ly / (sqrt(2.0f) * sqrt(gamma - lx * sqrt(gamma)));
			float qx = 0.0f;
			float qy = 0.0f;
			float qz = sqrt(gamma - lx * sqrt(gamma)) / sqrt(2.0f * gamma);

			InitQuaternion(qMag, qw, qx, qy, qz);
		}

		// Check the parameters.
        float magFactor = beta;

        if (adaptive) {
            magFactor = AdaptiveGain(*previousBeta, accRg, adaptiveGainFirstThreshold, adaptiveGainSecondThreshold, h);
            *previousBeta = magFactor;
        } else {
            *previousBeta = beta;
        }

		float _qMag[4];
		//InitQuaternion(_qMag, 1.0f, 0.0f, 0.0f, 0.0f);
		Slerp(qMag, magFactor, magnetometerSlerpTreshold, _qMag);
		MultiplyQuat(_Quat, _qMag, Quat);
		NormalizeQuaternion(Quat);
        CopyMatrix(Quat, PreviousQuat, 4, 1);
	}

    /* Use of a 3-axis accelerometer and magnetometer without a gyrometer */
    // It is preferable to filter the raw measurements before merging them for better estimates.
    // Not using a gyrometer is valid for applications where accuracy is not a priority.
	else if (accOK && magOK) {
		// Determine the partial orientation as a quaternion from the accelerometer measurements.
		//if (az >= 0) {
		if (az < 0.0f) {
			/*
			float qw = sqrt((az + 1.0f) / 2.0f);
			float qx = -ay / sqrt(2.0f * (1.0f - ax));
			float qy = ax / sqrt(2.0f * (az + 1.0f));
			float qz = 0.0f;
			*/

			float l1 = sqrt((1.0f - az) / 2.0f);
			float qw = l1;
			float qx = ay / (2.0f * l1);
			float qy = -ax / (2.0f * l1);
			float qz = 0.0f;

			InitQuaternion(qAcc, qw, qx, qy, qz);
		} else {
			/*
			float qw = -ay / sqrt(2.0f * (1.0f - az));
			float qx = sqrt((1.0f - az) / 2.0f);
			float qy = 0.0f;
			float qz = ax / sqrt(2.0f * (1.0f - az));
			*/

			float l2 = sqrt((1.0f + az) / 2.0f);
			float qw = ay / (2.0f * l2);
			float qx = l2;
			float qy = 0.0f;
			float qz = -ax / (2.0f * l2);

			InitQuaternion(qAcc, qw, qx, qy, qz);
		}

		// Determine the partial orientation in the form of a quaternion from the magnetometer measurements.
		float Racc[9];
		InitMatrix(Racc, 3, 3);
		QuaternionToDCM(qAcc, Racc);
		//QuaternionToRotMatrix(qAcc, Racc);
		Transpose(Racc, 3, 3);
		float magRg[3];
		Multiply(Racc, 3, 3, mag, 3, 1, magRg);

		float lx = GetElement(magRg, 3, 1, 0, 0);
		float ly = GetElement(magRg, 3, 1, 1, 0);
		float gamma = lx * lx + ly * ly;

		if (lx >= 0.0f) {
			float qw = sqrt(gamma + lx * sqrt(gamma)) / sqrt(2.0f * gamma);
			float qx = 0.0f;
			float qy = 0.0f;
			float qz = ly / (sqrt(2.0f) * sqrt(gamma + lx * sqrt(gamma)));

			InitQuaternion(qMag, qw, qx, qy, qz);
		} else {
			float qw = ly / (sqrt(2.0f) * sqrt(gamma - lx * sqrt(gamma)));
            float qx = 0.0f;
            float qy = 0.0f;
            float qz = sqrt(gamma - lx * sqrt(gamma)) / sqrt(2.0f * gamma);

            InitQuaternion(qMag, qw, qx, qy, qz);
		}

		// Determine the orientation in the form of a quaternion from the previous (partial) quaternions.
		MultiplyQuat(qAcc, qMag, Quat);
		NormalizeQuaternion(Quat);
	}
}
