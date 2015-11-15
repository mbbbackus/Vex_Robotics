int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;

//calculates the analog stick's axis to identify how far it is from the center
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

//basic drive function for the mechanum wheels
//loops continuously
void mdrive()
{
	deadZoneCheck();

	//Remote Control Commands
	motor[FrontRightDrive] = Y1 - X2 - X1;
	motor[BackRightDrive] =  Y1 - X2 + X1;
	motor[FrontLeftDrive] = Y1 + X2 + X1;
	motor[BackLeftDrive] =  Y1 + X2 - X1;
}

//function that controls the intake
//loops continuously as the button is pressed
void checkintake() // 1 forward, 0 backward
{

	//if button 6U (onCNTRL2) is pressed, run intake and outtake at -100
	if(vexRT[Btn6UXmtr2] == 1){
		motor[Intake] = -100;
	}
	//if button 6D (onCNTRL2) is pressed, run intake and outtake at 100
	else
		if(vexRT[Btn6DXmtr2] == 1){
		motor[Intake] = 100;
	}
	//in any other situation, dont run
	else {
		motor[Intake] = 0;
	}
}

//function that controls the power of the launcher
//loops continuosly as the button is pressed
task launcher()
{
	// Highest -------> Lowest
	// 7U 7R 7D 7L 8U 8R 8D 8L
	while(1==1){
		//None pressed
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 0){
			motor[LauncherLeftOutside] =  0;
			motor[LauncherRightOutside] = 0;
			motor[LauncherLeftInside] =   0;
			motor[LauncherRightInside] =  0;
		}
		//7L -- Lowest
		if(vexRT[Btn7LXmtr2] == 1 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 0){
			ClearTimer(T1);
			while(time1[T1] < 1000){
				motor[LauncherLeftOutside] = -55;
				motor[LauncherRightOutside] = -55;
				motor[LauncherLeftInside] = -55;
				motor[LauncherRightInside] = -55;
			}
			while(vexRT[Btn7LXmtr2] == 1){
				motor[LauncherLeftOutside] = -40;
				motor[LauncherRightOutside] = -40;
				motor[LauncherLeftInside] = -40;
				motor[LauncherRightInside] = -40;
			}
		}
		//7U -- Medium
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 1 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 0){
			ClearTimer(T1);
			while(time1[T1] < 1000){
				motor[LauncherLeftOutside] = -62;
				motor[LauncherRightOutside] = -62;
				motor[LauncherLeftInside] = -62;
				motor[LauncherRightInside] = -62;
			}
			while(vexRT[Btn7UXmtr2] == 1){
				motor[LauncherLeftOutside] = -47;
				motor[LauncherRightOutside] = -47;
				motor[LauncherLeftInside] = -47;
				motor[LauncherRightInside] = -47;
			}
		}
		//7R -- High
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 1 && vexRT[Btn7DXmtr2] == 0){
			ClearTimer(T1);
			while(time1[T1] < 1000){
				motor[LauncherLeftOutside] = -66;
				motor[LauncherRightOutside] = -66;
				motor[LauncherLeftInside] = -66;
				motor[LauncherRightInside] = -66;
			}
			while(vexRT[Btn7RXmtr2] == 1){
				motor[LauncherLeftOutside] = -55;
				motor[LauncherRightOutside] = -55;
				motor[LauncherLeftInside] = -55;
				motor[LauncherRightInside] = -55;
			}
		}
		//7D -- Field-Centric
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 1 ){
			/*motor[LauncherLeftOutside] =  -1 * launcherPower;
			motor[LauncherRightOutside] = -1 * launcherPower;
			motor[LauncherLeftInside] =   -1 * launcherPower;
			motor[LauncherRightInside] =  -1 * launcherPower;
			*/
			ClearTimer(T1);
			while(time1[T1] < 1000){
				motor[LauncherLeftOutside] = -70;
				motor[LauncherRightOutside] = -70;
				motor[LauncherLeftInside] = -70;
				motor[LauncherRightInside] = -70;
			}
			while(vexRT[Btn7DXmtr2] == 1){
				motor[LauncherLeftOutside] = -60;
				motor[LauncherRightOutside] = -60;
				motor[LauncherLeftInside] = -60;
				motor[LauncherRightInside] = -60;
			}

		}
	}

}

//function that allows for the control of the turntable
void turntable()
{
	if(vexRT[Btn5UXmtr2] == 0 && vexRT[Btn5DXmtr2] == 0){
		motor[Turntable] = 0;
	}
	if(vexRT[Btn5UXmtr2] == 1){
		motor[Turntable] = 100;
	}
	if(vexRT[Btn5DXmtr2] == 1){
		motor[Turntable] = -100;
	}
}

//function controls the power of the intake
void grab(int power)
{
	motor[Intake] = -power;
}

//Positive values drive the robot forward, Negative values drive it backward
void driveStraight(int power)
{
	motor[FrontRightDrive] = power;
	motor[BackRightDrive] =  power;
	motor[FrontLeftDrive] = power;
	motor[BackLeftDrive] =  power;
}

//positive values allow the robot to strafe right, Negative values allow the robot to strafe left
void strafe(int power)
{
	motor[FrontRightDrive] = -power;
	motor[BackRightDrive] =  power;
	motor[FrontLeftDrive] = power;
	motor[BackLeftDrive] =  -power;
}

//Positive values rotate the robot right, Negative values rotate the robot left
void rotate(int power)
{
	motor[FrontRightDrive] = -power;
	motor[BackRightDrive] =  -power;
	motor[FrontLeftDrive] = power;
	motor[BackLeftDrive] =  power;
}

//Positive values rotate the launcher right, Negative values rotate the launcher left 
void turnLauncher(int power)
{
	motor[Turntable] = power;
}

//function that allows for the user to launch a ball at a given power
//potentially for use in autonomous
void launch(int power)
{
	motor[LauncherLeftOutside] =  -power;
	motor[LauncherRightOutside] = -power;
	motor[LauncherLeftInside] =   -power;
	motor[LauncherRightInside] =  -power;

}
