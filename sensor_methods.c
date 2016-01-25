void getEncoderDeltas()
{
	//get initial enc vals
	se_backLeftLastVal = SensorValue[BackLeftEncoder];
	se_frontLeftLastVal = SensorValue[FrontLeftEncoder];
	se_backRightLastVal = SensorValue[BackRightEncoder];
	se_frontRightLastVal = SensorValue[FrontRightEncoder];

	ime_frontLeftLastVal = SensorValue[I2C_1];
	ime_backLeftLastVal = SensorValue[I2C_2];
	ime_backRightLastVal = SensorValue[I2C_3];
	ime_frontRightLastVal = SensorValue[I2C_4];

	wait1Msec(25);

	se_backLeftCurVal = SensorValue[BackLeftEncoder];
	se_frontLeftCurVal = SensorValue[FrontLeftEncoder];
	se_backRightCurVal = SensorValue[BackRightEncoder];
	se_frontRightCurVal = SensorValue[FrontRightEncoder];

	ime_frontLeftCurVal = SensorValue[I2C_1];
	ime_backLeftCurVal = SensorValue[I2C_2];
	ime_backRightCurVal = SensorValue[I2C_3];
	ime_frontRightCurVal = SensorValue[I2C_4];

	se_backLeftDelta = se_backLeftCurVal - se_backLeftLastVal;
	se_frontLeftDelta = se_frontLeftCurVal - se_frontLeftLastVal;
	se_backRightDelta = se_backRightCurVal - se_backRightLastVal;
	se_frontRightDelta = se_frontRightCurVal - se_frontRightLastVal;

	ime_backLeftDelta = ime_backLeftCurVal - ime_backLeftLastVal;
	ime_frontLeftDelta = ime_frontLeftCurVal - ime_frontLeftLastVal;
	ime_backRightDelta = ime_backRightCurVal - ime_backRightLastVal;
	ime_frontRightDelta = ime_frontRightCurVal - ime_frontRightLastVal;
}

float toInches(int encoderVal, float ticks)
{
	float circumference = pi * 4.0;
	return ((float) encoderVal / ticks) * circumference;
}

//drive straight for distance set in inches
void moveDistance(float distanceSet)
{
	float distanceTraveled = 0;
	while(distanceTraveled < distanceSet)
	{
		getEncoderDeltas();
		se_left_distance = (toInches(se_backLeftDelta, 90.0) + toInches(se_frontLeftDelta, 90.0)) / 2.0;
		se_right_distance = (toInches(se_backRightDelta, 90.0) + toInches(se_frontRightDelta, 90.0)) / 2.0;
		ime_left_distance = (toInches(ime_backLeftDelta, 627.2) + toInches(ime_frontLeftDelta, 627.2)) / 2.0;
		ime_left_distance = (toInches(ime_backRightDelta, 627.2) + toInches(ime_frontRightDelta, 627.2)) / 2.0;

		right_distance = (se_right_distance + ime_right_distance) / 2.0;
		left_distance = (se_left_distance + ime_left_distance) / 2.0;

		float distance_avg = (right_distance + left_distance) / 2.0;
		distanceTraveled += distance_avg;
		powerDriveBase(63,63);
	}
}
