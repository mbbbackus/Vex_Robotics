//Continuously updated values
double robotXPos = 0.0;
double robotYPos = 0.0;
double robotDir = 0.0;

bool blue = false;
bool red  = false;

double redGoalX = 12.0;
double redGoalY = 128.0;

double blueGoalX = 128.0;
double blueGoalY = 128.0;

double robotGoalXDiff = 0;
double robotGoalYDiff = 0;

//The relative difference between the actual direction and gyro value
double dirDifference = 0.0;

//Initial position values
double xInit = 0.0;
double yInit = 0.0;
double dirInit = 0.0;

//Position Deltas
double xChange = 0.0;
double yChange = 0.0;

//Speed values updated by integrated motor encoders
double leftBackSpeed = 0.0;
double leftFrontSpeed = 0.0;
double rightBackSpeed = 0.0;
double rightFrontSpeed = 0.0;

//Change in distance of each wheel in inches
double lb = 0.0;
double rb = 0.0;
double lf = 0.0;
double rf = 0.0;

//Four functions for each starting position
void setLeftBlue()
{
	xInit = 12;
	yInit = 36;
	dirInit = 45;
	blue = true;
}
void setRightBlue()
{
	xInit = 36;
	yInit = 12;
	dirInit = 45;
	blue = true;
}
void setLeftRed()
{
	xInit = 104;
	yInit = 12;
	dirInit = 135;
	red = false;
}
void setRightRed()
{
	xInit = 128;
	yInit = 36;
	dirInit = 135;
	red = false;
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
		//Adds inches moved to each lb... value
		lb = leftBackSpeed   / 10.0; //Divided by ten because the encoder checks RPM every tenth of a second
		rb = rightBackSpeed  / 10.0;
		lf = leftFrontSpeed  / 10.0;
		rf = rightFrontSpeed / 10.0;
		return 1;
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

double calcLauncherPower(){
	if(red){
		robotGoalXDiff = redGoalX - robotXPos;
		robotGoalYDiff = redGoalY - robotYPos;
	}
	if(blue){
		robotGoalXDiff = blueGoalX - robotXPos;
		robotGoalYDiff = blueGoalY - robotYPos;
	}
	//field diagonal length is 181
	double xPow = pow(robotGoalXDiff, 2);
	double yPow = pow(robotGoalYDiff, 2);
	return pow(xPow + yPow, 0.5) / 182.0;

}

//Update values
void updatePositionValues()
{
	if(calcWheelChange() == 1){
		calcXYComponents();
		robotXPos = robotXPos + xChange;
		robotYPos = robotYPos + yChange;
	}
	robotDir = (SensorValue[BaseGyro] / 10.0) - dirDifference;
	if(robotDir < 0) robotDir += 360;
}

//Calibration function - resets initial direction value to 0
void dirButtons()
{
	if(vexRT[Btn7UXmtr2] == 1){
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
		//displayNextLCDNumber(robotDir);
		displayNextLCDNumber(calcLauncherPower());
		wait1Msec(100);
	}
}
