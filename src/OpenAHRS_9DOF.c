/**************************************************************
* OpenAHRS                                                    *
* $ Id: OpenAHRS_9DOF.c v1.0 22/11/2023 22:45 t.borensztejn $ *
**************************************************************/

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

#include <string.h>

#include "../includes/ARFilter.h"
#include "../includes/AQUAFilter.h"
#include "../includes/DavenportFilter.h"

uint8_t main(void) {
    uint8_t ret = 0;
    uint16_t niter = 6; // Number of iterations.
    float Ts = 0.004f;  // Sampling period (s).
    char line[256];     // Readed CSV file line.

    float IdentityQuat[4];  // Identity quaternion.
    float Quat[4];          // Quaternion representing actual orientation.
    float PreviousQuat[4];  // Quaternion representing previous orientation.

    GyroscopeRawMeasurements Gyr;       // Structure containing gyroscope raw measurements.
    AccelerometerRawMeasurements Acc;   // Structure containing accelerometer raw measurements.
    MagnetometerRawMeasurements Mag;    // Structure containing magnetometer raw measurements.
    TaitBryanAngles Angles;             // Structure containing roll, pitch and yaw angles.

    Gyr.p = 0.0f;
    Gyr.q = 0.0f;
    Gyr.r = 0.0f;

    Acc.ax = 0.0f;
    Acc.ay = 0.0f;
    Acc.az = 0.0f;

    Mag.mx = 0.0f;
    Mag.my = 0.0f;
    Mag.mz = 0.0f;

    Angles.phi = 0.0f;
    Angles.theta = 0.0f;
    Angles.psi = 0.0f;

    FILE *CSVFile = fopen("raw_measurements.csv", "r");

    InitQuaternion(IdentityQuat, 1.0f, 0.0f, 0.0f, 0.0f);
    CopyMatrix(IdentityQuat, Quat, 4, 1);
    CopyMatrix(IdentityQuat, PreviousQuat, 4, 1);

    /* AQUA filter parameters. */

    float alpha = 0.01f;            // Add description here.
    float previousAlpha = 0.0f;     // Add description here.
    float beta = 0.01f;             // Add description here.
    float previousBeta = 0.0f;      // Add description here.
    float t1 = 0.1f;                // Add description here.
    float t2 = 0.2f;                // Add description here.
    float t3 = 0.9f;                // Add description here.
    float t4 = 0.9f;                // Add description here.
    float g = 9.81f;                // Add description here.
    float h = 48.0f;                // Add description here.

    /* Davenport filter paramters. */

    float mdip = 0.0f;
    float w1 = 1.0f;
    float w2 = 1.0f;

    if (CSVFile == NULL) {
        printf("Error opening CSV file.\n");
        ret = 1;
    } else {
        fgets(line, sizeof(line), CSVFile);

        /* Functionality of the AR filter validated. */
        /*
        for (uint16_t n = 0; n < niter; n++) {
            int8_t result;

            //UpdateARFilter(&Gyr, Quat, PreviousQuat, Ts, 3, SERIES);

            if (fgets(line, sizeof(line), CSVFile) != NULL) {
                result = sscanf(line, "%f,%f,%f,%f,%f,%f,%f,%f,%f", &Acc.ax, &Acc.ay, &Acc.az, &Gyr.p, &Gyr.q, &Gyr.r, &Mag.mx, &Mag.my, &Mag.mz);
            }

            //UpdateARFilter(&Gyr, Quat, PreviousQuat, Ts, 0, CLOSED);
            UpdateARFilter(&Gyr, Quat, PreviousQuat, Ts, 3, SERIES);
            QuaternionToTaitBryanAngles(Quat, &Angles);
            //PrintMatrix(Quat, 4, 1);

            printf("X: %.3f\n", Degrees(Angles.phi));
            printf("Y: %.3f\n", Degrees(Angles.theta));
            printf("Z: %.3f\n", Degrees(Angles.psi));
            printf("\n");
        }
        */

        /* Functionality of the AQUA filter validated. */
        /*
        for (uint16_t n = 0; n < niter; n++) {
            int8_t result;

            if (fgets(line, sizeof(line), CSVFile) != NULL) {
                result = sscanf(line, "%f,%f,%f,%f,%f,%f,%f,%f,%f", &Acc.ax, &Acc.ay, &Acc.az, &Gyr.p, &Gyr.q, &Gyr.r, &Mag.mx, &Mag.my, &Mag.mz);
            }

            UpdateAQUAFilter(&Acc, &Gyr, &Mag, Quat, PreviousQuat, Ts, 0, alpha, &previousAlpha, beta, &previousBeta, t1, t2, t3, t4, g, h);
            QuaternionToTaitBryanAngles(Quat, &Angles);
            //PrintMatrix(Quat, 4, 1);

            printf("X: %.3f\n", Degrees(Angles.phi));
            printf("Y: %.3f\n", Degrees(Angles.theta));
            printf("Z: %.3f\n", Degrees(Angles.psi));
            printf("\n");
        }
        */

        /* Functionality of the Davenport filter validated. */
        for (uint16_t n = 0; n < niter; n++) {
            int8_t result;

            if (fgets(line, sizeof(line), CSVFile) != NULL) {
                result = sscanf(line, "%f,%f,%f,%f,%f,%f,%f,%f,%f", &Acc.ax, &Acc.ay, &Acc.az, &Gyr.p, &Gyr.q, &Gyr.r, &Mag.mx, &Mag.my, &Mag.mz);
            }

            UpdateDavenportQMethodFilter(&Acc, &Mag, Quat, PreviousQuat, Ts, w1, w2, g, mdip);
            QuaternionToTaitBryanAngles(Quat, &Angles);
            //PrintMatrix(Quat, 4, 1);

            printf("X: %.3f\n", Degrees(Angles.phi));
            printf("Y: %.3f\n", Degrees(Angles.theta));
            printf("Z: %.3f\n", Degrees(Angles.psi));
            printf("\n");
        }

        fclose(CSVFile);
    }

    return ret;
}
