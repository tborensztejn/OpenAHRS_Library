import numpy as np
import csv

def GenerateRawMeasurements(rollAngle, pitchAngle, yawAngle, previousRollAngle, previousPitchAngle, previousYawAngle, Te = 0.1):
    # Declaration of constants.
    g = 9.81
    B = 48.0
    #i = 35.0
    i = 0.0

    Vacc_Rg = np.matrix([0, 0, -g])    # Gravity vector in the fixed frame (reference frame).
    #Vacc_Rg = np.matrix([0, 0, g])

    # Convert angles to radians.
    phi = np.radians(rollAngle)
    theta = np.radians(pitchAngle)
    psi = np.radians(yawAngle)

    # Magnetic field vector components in the fixed frame.
    Bx = B * np.cos(np.radians(i))
    By = 0.0
    Bz = -B * np.sin(np.radians(i))

    # Convert angles to radians.
    previousPhi = np.radians(previousRollAngle)
    previousTheta = np.radians(previousPitchAngle)
    previousPsi = np.radians(previousYawAngle)

    # Calculate angular rates.
    d_phi = (phi - previousPhi) / Te
    d_theta = (theta - previousTheta) / Te
    d_psi = (psi - previousPsi) / Te

    Vmag_Rg = np.matrix([Bx, By, Bz])              # Magnetic field vector in the fixed frame.
    Vgyr_Rg = np.matrix([d_phi, d_theta, d_psi])   # Gyro measurements vector in the fixe frame.

    # Rotation matrices.
    Rx = np.array([
        [1, 0, 0],
        [0, np.cos(phi), -np.sin(phi)],
        [0, np.sin(phi), np.cos(phi)]
    ])

    Ry = np.array([
        [np.cos(theta), 0, np.sin(theta)],
        [0, 1, 0],
        [-np.sin(theta), 0, np.cos(theta)]
    ])

    Rz = np.array([
        [np.cos(psi), -np.sin(psi), 0],
        [np.sin(psi), np.cos(psi), 0],
        [0, 0, 1]
    ])

    Omega = np.array([
        [1.0,	np.sin(phi) * np.tan(theta),	np.cos(phi) * np.tan(theta)],
        [0.0,	np.cos(phi),			-np.sin(phi)],
        [0.0,	np.sin(phi) / np.cos(theta),	np.cos(phi) / np.cos(theta)]
    ])

    # Sensor measurements in the sensor frame.
    Rzyx = np.matmul(np.matmul(Rz, Ry), Rx)
    Vacc_Rs = np.matmul(Rzyx, np.transpose(Vacc_Rg))
    Vmag_Rs = np.matmul(Rzyx, np.transpose(Vmag_Rg))
    OmegaInv = np.linalg.inv(Omega)
    Vgyr_Rs = np.matmul(OmegaInv, np.transpose(Vgyr_Rg))

    return Vacc_Rs, Vmag_Rs, Vgyr_Rs

def main():
    # Parameters.
	Te = 0.004
	niter = 6              # Number of samples to generate.
	rollAmplitude = 10.0   # Roll amplitude in degrees.
	rollFrequency = 0.2    # Roll frequency in Hz.
	pitchAmplitude = -5.0  # Pitch amplitude in degrees.
	pitchFrequency = 0.5   # Pitch frequency in Hz.
	yawAmplitude = 15.0    # Yaw amplitude in degrees.
	yawFrequency = 0.1     # Yaw frequency in Hz.

    # Generate sinusoidal motion for roll, pitch, and yaw.
	roll = rollAmplitude * np.sin(2.0 * np.pi * rollFrequency * np.arange(niter) * Te)
	roll = np.zeros(niter)
	roll = [0, 1, 2, 3, 4, 5]
	pitch = pitchAmplitude * np.sin(2.0 * np.pi * pitchFrequency * np.arange(niter) * Te)
	pitch = np.zeros(niter)
	pitch = [0, 1, 2, 3, 4, 5]
	yaw = yawAmplitude * np.sin(2.0 * np.pi * yawFrequency * np.arange(niter) * Te)
	yaw = np.zeros(niter)
	yaw = [0, 2, 4, 6, 8, 10]

	"""
	r = np.empty_like(roll, dtype=object)
	t = np.empty_like(pitch, dtype=object)
	l = np.empty_like(yaw, dtype=object)

	for i in range(len(roulis)):
		r[i] = "{:.3f}".format(roll[i])
		t[i] = "{:.3f}".format(pitch[i])
		l[i] = "{:.3f}".format(yaw[i])

	print(r)
	print(t)
	print(l)
	"""

	with open('build/raw_measurements.csv', 'w', newline='') as FichierCSV:
		#columnNames = ['ax', 'ay', 'az', 'gx', 'gy', 'gz', 'mx', 'my', 'mz', 'phi', 'theta', 'psi']
		columnNames = ['ax', 'ay', 'az', 'gx', 'gy', 'gz', 'mx', 'my', 'mz'] # Define column names.
		e = csv.DictWriter(FichierCSV, fieldnames=columnNames)
		e.writeheader()

		for n in range(niter):
            # Generate raw measurements for each time step.
			Vacc_Rs = None
			Vmag_Rs = None
			Vgyr_Rs = None

			if n > 0:
				Vacc_Rs, Vmag_Rs, Vgyr_Rs = GenerateRawMeasurements(roll[n], pitch[n], yaw[n], roll[n-1], pitch[n-1], yaw[n-1], Te)
			else:
				Vacc_Rs, Vmag_Rs, Vgyr_Rs = GenerateRawMeasurements(roll[n], pitch[n], yaw[n], 0.0, 0.0, 0.0, Te)

			#Vgyr_Rs = np.zeros((3, 1))

			"""
			ligne = {
				'ax': format(Vacc_Rs[0, 0], '.3f'),
				'ay': format(Vacc_Rs[1, 0], '.3f'),
				'az': format(Vacc_Rs[2, 0], '.3f'),
				'gx': format(Vgyr_Rs[0, 0], '.3f'),
				'gy': format(Vgyr_Rs[1, 0], '.3f'),
				'gz': format(Vgyr_Rs[2, 0], '.3f'),
				'mx': format(Vmag_Rs[0, 0], '.3f'),
				'my': format(Vmag_Rs[1, 0], '.3f'),
				'mz': format(Vmag_Rs[2, 0], '.3f'),
				'phi': format(roulis[n], '.3f'),
				'theta': format(tangage[n], '.3f'),
				'psi': format(lacet[n], '.3f')
			}
			"""

            # Write the measurements to the CSV file.
			ligne = {
				'ax': format(Vacc_Rs[0, 0], '.3f'),
				'ay': format(Vacc_Rs[1, 0], '.3f'),
				'az': format(Vacc_Rs[2, 0], '.3f'),
				'gx': format(Vgyr_Rs[0, 0], '.3f'),
				'gy': format(Vgyr_Rs[1, 0], '.3f'),
				'gz': format(Vgyr_Rs[2, 0], '.3f'),
				'mx': format(Vmag_Rs[0, 0], '.3f'),
				'my': format(Vmag_Rs[1, 0], '.3f'),
				'mz': format(Vmag_Rs[2, 0], '.3f')
			}

			e.writerow(ligne)

if __name__ == "__main__":
	main()
