int fieldWidth = 140.5; //inches
int robotXPos = 0;
int robotYPos = 0;
int robotDir = 0;

void changePos(int diffX, int diffY, int diffDir)
{
	robotXPos = robotXPos + diffX;
	robotYPos = robotYPos + diffY;
	robotDir = robotDir + diffDir;
}

void setLeftBlue()
{
	changePos(12, 36, 45);
}
void setRightBlue()
{
	changePos(36, 12, 45);
}
void setLeftRed()
{
	changePos(104, 12, 135);
}
void setRightRed()
{
	changePos(128, 36, 135);
}

int calcWheelChange()
{

}

task lcdtask()
{
	float leftBackSpeed = 0 ;
	float leftFrontSpeed = 0;
	float rightBackSpeed = 0;
	float rightFrontSpeed = 0;

	float lb = 0;
	float rb = 0;
	float lf = 0;
	float rf = 0;

	while(1 == 1)
	{
		leftBackSpeed = SmartMotorGetSpeed(port2)   / 60 * 12.56; //2r*pi = 12.56
		rightBackSpeed = SmartMotorGetSpeed(port3)  / 60 * 12.56;
		leftFrontSpeed = SmartMotorGetSpeed(port6)  / 60 * 12.56;
		rightFrontSpeed = SmartMotorGetSpeed(port5) / 60 * 12.56;

		if(abs(leftBackSpeed) > 12 || abs(rightBackSpeed) > 12 || abs(leftFrontSpeed) > 12 || abs(rightFrontSpeed) > 12)
		{
			lb = lb + (leftBackSpeed   / 10);
			rb = rb + (rightBackSpeed  / 10);
			lf = lf + (leftFrontSpeed  / 10);
			rf = rf + (rightFrontSpeed / 10);

			clearLCDLine(0);
			clearLCDLine(1);
			displayLCDString(0,0,"front: ");
			displayNextLCDNumber(lf);
			displayNextLCDString(",");
			displayNextLCDNumber(rf);
			displayLCDString(1,0,"back: ");
			displayNextLCDNumber(lb);
			displayNextLCDString(",");
			displayNextLCDNumber(rb);
			wait1Msec(100);
		}
	}
}
