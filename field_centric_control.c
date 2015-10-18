//Continuously updated values
float robotXPos = 0;
float robotYPos = 0;
float robotDir = 0;

//The relative difference between the actual direction and gyro value
float dirDifference = 0;

//Initial position values
float xInit = 0;
float yInit = 0;
float dirInit = 0;

//Position Deltas
float xChange = 0;
float yChange = 0;

//Speed values updated by integrated motor encoders
float leftBackSpeed = 0 ;
float leftFrontSpeed = 0;
float rightBackSpeed = 0;
float rightFrontSpeed = 0;

//Change in distance of each wheel in inches
float lb = 0;
float rb = 0;
float lf = 0;
float rf = 0;

//Four functions for each starting position
void setLeftBlue()
{
	xInit = 12;
	yInit = 36;
	dirInit = 45;
}
void setRightBlue()
{
	xInit = 36;
	yInit = 12;
	dirInit = 45;
}
void setLeftRed()
{
	xInit = 104;
	yInit = 12;
	dirInit = 135;
}
void setRightRed()
{
	xInit = 128;
	yInit = 36;
	dirInit = 135;
}

//Compares initial gyro value to what initial dir should be
//If gyro is negative, adds 360
//Continously calibrates values and initializes
void calcDirectionDifference()
{
	if(SensorValue[BaseGyro] < 0) dirDifference = (SensorValue[BaseGyro] / 10.0) + 360.0 - dirInit;
	else dirDifference = (SensorValue[BaseGyro] / 10.0) - dirInit;
}

//updates changes in wheel distances, checks integrated motor encoder values
//returns 1 if robot is actually moving (not just motors) else returns 0
int calcWheelChange()
{
	SensorValue[RightEncoder] = 0.0;
	SensorValue[LeftEncoder] = 0.0;
	leftBackSpeed = SmartMotorGetSpeed(port2)   / 60.0 * 12.56; //4*pi = 12.56
	rightBackSpeed = SmartMotorGetSpeed(port3)  / 60.0 * 12.56;
	leftFrontSpeed = SmartMotorGetSpeed(port6)  / 60.0 * 12.56;
	rightFrontSpeed = SmartMotorGetSpeed(port5) / 60.0 * 12.56;
	//Checks the six encoders - resets shaft encoders and calculates speed of integrated motors
	//Integrated = RPM / minute * circumference = inches / second

	//Checks if Robot is moving and motors are powered
	if(abs(leftBackSpeed) > 1 || abs(rightBackSpeed) > 1 || abs(leftFrontSpeed) > 1 || abs(rightFrontSpeed) > 1)//Making sure enough power to actually move
	{
		if(SensorValue[RightEncoder] != 0 || SensorValue[LeftEncoder] != 0)//Checking if robot actually moving w/ shaft encoders
		{
			//Adds inches moved to each lb... value
			lb = leftBackSpeed   / 10.0; //Divided by ten because the encoder checks RPM every tenth of a second
			rb = rightBackSpeed  / 10.0;
			lf = leftFrontSpeed  / 10.0;
			rf = rightFrontSpeed / 10.0;
			return 1;
		}
		else return 0;
	}
	//Check if robot is coasting (motors aren't working but wheels are turning)
	if(SensorValue[RightEncoder] != 0 || SensorValue[LeftEncoder] != 0)
	{
		//shaft encoder has 90 ticks
		lb = SensorValue[LeftEncoder]  / 90.0 * 8.64 ; //2.75*pi = 8.64
		lf = SensorValue[LeftEncoder]  / 90.0 * 8.64 ;

		//right sensor is inverted
		rb = SensorValue[RightEncoder] / 90.0 * 8.64 ;
		rf = SensorValue[RightEncoder] / 90.0 * 8.64 ;
		return 1;
	}
	return 0;
}

//Calculates the change in X and Y at instant using inches traveled and trigonometric functions
void calcXYComponents()
{
	//Check if moving forward
	if(lb > 0 && rb > 0 && lf > 0 && rf > 0)
	{
		xChange = (lb + lf + rb + rf) / 4.0 * cosDegrees(robotDir);
		yChange = (lb + lf + rb + rf) / 4.0 * sinDegrees(robotDir);
	}
	//Check if moving backward
	else if(lb < 0 && rb < 0 && lf < 0 && rf < 0)
	{
		xChange = (lb + lf + rb + rf) / 4.0 * cosDegrees(robotDir);
		yChange = (lb + lf + rb + rf) / 4.0 * sinDegrees(robotDir);
	}
	//Check if turning left
	else if(lb < 0 && rb > 0 && lf < 0 && rf > 0)
	{
		xChange = (lb + lf + rb + rf) / 4.0 * cosDegrees(robotDir);
		yChange = (lb + lf + rb + rf) / 4.0 * sinDegrees(robotDir);
	}
	//Check if turning right
	else if(lb > 0 && rb < 0 && lf > 0 && rf < 0)
	{
		xChange = (lb + lf + rb + rf) / 4.0 * cosDegrees(robotDir);
		yChange = (lb + lf + rb + rf) / 4.0 * sinDegrees(robotDir);
	}
	//Check if strafing left
	else if(lb < 0 && rb > 0 && lf > 0 && rf < 0)
	{
		xChange = (abs(lb) + abs(lf) + abs(rb) + abs(rf)) / 4.0 * cosDegrees(robotDir + 90.0);
		yChange = (abs(lb) + abs(lf) + abs(rb) + abs(rf)) / 4.0 * sinDegrees(robotDir + 90.0);

	}
	//Check if strafing right
	else if(lb > 0 && rb < 0 && lf < 0 && rf > 0)
	{
		//The minus 90 is because when strafing, it's moving as if robot was point 90 degrees clockwise
		xChange = (abs(lb) + abs(lf) + abs(rb) + abs(rf)) / 4.0 * sinDegrees(robotDir - 90.0);
		yChange = (abs(lb) + abs(lf) + abs(rb) + abs(rf)) / 4.0 * sinDegrees(robotDir - 90.0);
	}
}

//Update values
void updatePositionValues()
{
	if(calcWheelChange() == 1){
		calcXYComponents();
		robotXPos = robotXPos + xChange;
		robotYPos = robotYPos + yChange;
		robotDir = (SensorValue[BaseGyro] / 10.0) - dirDifference;
	}
}

//Calibration function - resets initial direction value to 0
void dirButtons()
{
	if(vexRT[Btn7U] == 1){
		calcDirectionDifference();
	}
	else{}
}

task lcdtask()
{

	while(1 == 1)
	{
		updatePositionValues();
		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDString(0,0,"X,Y: ");
		displayNextLCDNumber(robotXPos);
		displayNextLCDString(" , ");
		displayNextLCDNumber(robotYPos);
		displayLCDString(1,0,"Angle: ");
		displayNextLCDNumber(robotDir);
		wait1Msec(100);
	}
}
