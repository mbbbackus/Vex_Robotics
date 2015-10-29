int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;

//can move to other file, or remove
void deadZoneCheck()
{
	//Create "deadzone" for Y1/Ch3
	if(abs(vexRT[Ch3]) > threshold)
		Y1 = vexRT[Ch3];
	else
		Y1 = 0;
	//Create "deadzone" for X1/Ch4
	if(abs(vexRT[Ch4]) > threshold)
		X1 = vexRT[Ch4];
	else
		X1 = 0;
	//Create "deadzone" for X2/Ch1
	if(abs(vexRT[Ch1]) > threshold)
		X2 = vexRT[Ch1];
	else
		X2 = 0;
}

//Loop Forever
void mdrive()
{
		deadZoneCheck();

		//Remote Control Commands
		motor[FrontRightDrive] = Y1 - X2 - X1;
		motor[BackRightDrive] =  Y1 - X2 + X1;
		motor[FrontLeftDrive] = Y1 + X2 + X1;
		motor[BackLeftDrive] =  Y1 + X2 - X1;
}

//Loop this
void checkintake() // 1 forward, 0 backward
{

	//if button 6U (onCNTRL2) is pressed, run intake and outtake at -100
	if(vexRT[Btn6UXmtr2] == 1 || vexRT[Btn6UXmtr2] == 1){
		motor[Outtake] = -100;
		motor[Intake] = -100;
	}
	//if button 6D (onCNTRL2) is pressed, run intake and outtake at 100
	else
	if(vexRT[Btn6DXmtr2] == 1 || vexRT[Btn6DXmtr2] == 1){
		motor[Outtake] = 100;
		motor[Intake] = 100;
	}
	//in any other situation, dont run
	else {
	motor[Outtake] = 0;
	motor[Intake] = 0;
	}
}

//Loop this too
task launcher()
{
	// Highest -------> Lowest
	// 7U 7R 7D 7L 8U 8R 8D 8L
	while(1==1){
		//None pressed
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 0){
			motor[LauncherLeft] = 0;
			motor[LauncherRight] = 0;
		}
		//7L -- Lowest
		if(vexRT[Btn7LXmtr2] == 1 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 0){
			motor[LauncherLeft] = -50;
			motor[LauncherRight] = -50;
		}
		//7U -- Medium
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 1 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 0){
			motor[LauncherLeft] = -70;
			motor[LauncherRight] = -70;
		}
		//7R -- High
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 1 && vexRT[Btn7DXmtr2] == 0){
			motor[LauncherLeft] = -127;
			motor[LauncherRight] = -127;
		}
		//7D -- Field-Centric
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 1 ){
			ClearTimer(T1);
			while(time1[T1] < 1000){
				motor[LauncherLeft] = -80;
				motor[LauncherRight] = -80;
			}
			while(vexRT[Btn7DXmtr2] == 1){
				motor[LauncherLeft] = -1 * calcLauncherPower();
				motor[LauncherRight] = -1 * calcLauncherPower();
			}
		}
	}

}

//Turntable
void turntable()
{
		if(vexRT[Btn5UXmtr2] == 0 && vexRT[Btn5DXmtr2] == 0){
			motor[TurntableLeft] = 0;
			motor[TurntableRight] = 0;
		}
		if(vexRT[Btn5UXmtr2] == 1){
			motor[TurntableLeft] = 100;
			motor[TurntableRight] = 100;
		}
		if(vexRT[Btn5DXmtr2] == 1){
			motor[TurntableLeft] = -100;
			motor[TurntableRight] = -100;
		}
}


void grab(int power)
{
	motor[Outtake] = -power;
	motor[Intake] = -power;
}

//Positive forward, Negative backward
void driveStraight(int power)
{
	motor[FrontRightDrive] = power;
	motor[BackRightDrive] =  power;
	motor[FrontLeftDrive] = power;
	motor[BackLeftDrive] =  power;
}

//Positive power = right, Negative = Left
void strafe(int power)
{
	motor[FrontRightDrive] = -power;
	motor[BackRightDrive] =  power;
	motor[FrontLeftDrive] = power;
	motor[BackLeftDrive] =  -power;
}

//Positive power = right, Negative = left
void rotate(int power)
{
	motor[FrontRightDrive] = -power;
	motor[BackRightDrive] =  -power;
	motor[FrontLeftDrive] = power;
	motor[BackLeftDrive] =  power;
}

//Again, + right, - left
void turnLauncher(int power)
{
	motor[TurnTableLeft] = power;
	motor[TurnTableRight] = power;
}

void launch(int power)
{
	motor[LauncherLeft] = -power;
	motor[LauncherRight] = -power;
}
