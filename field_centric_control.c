float fieldWidth = 140.5; //inches
float robotXPos = 0;
float robotYPos = 0;
float robotDir = 0;

float xInit = 0;
float yInit = 0;
float dirInit = 0;

float leftBackSpeed = 0 ;
float leftFrontSpeed = 0;
float rightBackSpeed = 0;
float rightFrontSpeed = 0;

float lb = 0;
float rb = 0;
float lf = 0;
float rf = 0;

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

		//right sensor is inverted
		rb = rb - SensorValue[RightEncoder] / 90.0 * 8.64 ;
		rf = rf - SensorValue[RightEncoder] / 90.0 * 8.64 ;
		return 1;
	}
	return 0;
}

void dirButtons()
{
	if(vexRT[Btn7U] == 1){
		dirInit = 0;
	}
	else{}
}

task lcdtask()
{

	while(1 == 1)
	{
			if(calcWheelChange() == 1)
			{
				robotXPos = xInit - ((lb+lf+rb+rf)/4.0)
				robotYPos = yInit;
				if((dirInit + (SensorValue[BaseGyro]/10)) < 0) robotDir = 360 + (dirInit + (SensorValue[BaseGyro]/10));
				else robotDir = dirInit + SensorValue[BaseGyro]/10;
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
}
