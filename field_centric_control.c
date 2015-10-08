int fieldWidth = 140.5; //inches
int robotXPos = 0;
int robotYPos = 0;
int robotDir = 0;

float leftBackSpeed = 0 ;
float leftFrontSpeed = 0;
float rightBackSpeed = 0;
float rightFrontSpeed = 0;

float lb = 0;
float rb = 0;
float lf = 0;
float rf = 0;


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
	SensorValue[RightEncoder] = 0.0;
	SensorValue[LeftEncoder] = 0.0;
	leftBackSpeed = SmartMotorGetSpeed(port2)   / 60.0 * 12.56; //4*pi = 12.56
	rightBackSpeed = SmartMotorGetSpeed(port3)  / 60.0 * 12.56;
	leftFrontSpeed = SmartMotorGetSpeed(port6)  / 60.0 * 12.56;
	rightFrontSpeed = SmartMotorGetSpeed(port5) / 60.0 * 12.56;

	if(abs(leftBackSpeed) > 12 || abs(rightBackSpeed) > 12 || abs(leftFrontSpeed) > 12 || abs(rightFrontSpeed) > 12)
	{
		if(SensorValue[RightEncoder] != 0 || SensorValue[LeftEncoder] != 0)
		{
			lb = lb + (leftBackSpeed   / 10.0); //Divided by ten because the encoder checks RPM every tenth of a second
			rb = rb + (rightBackSpeed  / 10.0);
			lf = lf + (leftFrontSpeed  / 10.0);
			rf = rf + (rightFrontSpeed / 10.0);
			return 1;
		}
		return 0;
	}
	if(SensorValue[RightEncoder] != 0 || SensorValue[LeftEncoder] != 0)
	{
		//shaft encoder has 90 ticks
		lb = lb + SensorValue[LeftEncoder]  / 90.0 * 8.64 ; //2.75*pi = 8.64
		lf = lf + SensorValue[LeftEncoder]  / 90.0 * 8.64 ;
		rb = rb + SensorValue[RightEncoder] / 90.0 * 8.64 ;
		rf = rf + SensorValue[RightEncoder] / 90.0 * 8.64 ;
		return 1;
	}
	return 0;
}

task lcdtask()
{

	while(1 == 1)
	{
			if(calcWheelChange() == 1)
			{
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
