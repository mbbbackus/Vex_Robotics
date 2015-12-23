//basic drive function
void bdrive()
{
	//Remote Control Commands
	motor[FrontRightDrive] = vexRT[Ch2];
	motor[BackRightDrive] = vexRT[Ch2];
	motor[FrontLeftDrive] = vexRT[Ch3];
	motor[BackLeftDrive] =  vexRT[Ch3];
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
				motor[LauncherLeftOutside] = -60;
				motor[LauncherRightOutside] = -60;
				motor[LauncherLeftInside] = -60;
				motor[LauncherRightInside] = -60;
			}
			while(vexRT[Btn7LXmtr2] == 1){
				motor[LauncherLeftOutside] = -45;
				motor[LauncherRightOutside] = -45;
				motor[LauncherLeftInside] = -45;
				motor[LauncherRightInside] = -45;
			}
		}
		//7U -- Medium
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 1 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 0){
			ClearTimer(T1);
			while(time1[T1] < 1000){
				motor[LauncherLeftOutside] = -67;
				motor[LauncherRightOutside] = -67;
				motor[LauncherLeftInside] = -67;
				motor[LauncherRightInside] = -67;
			}
			while(vexRT[Btn7UXmtr2] == 1){
				motor[LauncherLeftOutside] = -50;
				motor[LauncherRightOutside] = -50;
				motor[LauncherLeftInside] = -50;
				motor[LauncherRightInside] = -50;
			}
		}
		//7R -- High
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 1 && vexRT[Btn7DXmtr2] == 0){
			ClearTimer(T1);
			while(time1[T1] < 1000){
				motor[LauncherLeftOutside] = -76;
				motor[LauncherRightOutside] = -76;
				motor[LauncherLeftInside] = -76;
				motor[LauncherRightInside] = -76;
			}
			while(vexRT[Btn7RXmtr2] == 1){
				motor[LauncherLeftOutside] = -56;
				motor[LauncherRightOutside] = -56;
				motor[LauncherLeftInside] = -56;
				motor[LauncherRightInside] = -56;
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
				motor[LauncherLeftOutside] = -83;
				motor[LauncherRightOutside] = -83;
				motor[LauncherLeftInside] = -83;
				motor[LauncherRightInside] = -83;
			}
			while(vexRT[Btn7DXmtr2] == 1){
				motor[LauncherLeftOutside] = -65;
				motor[LauncherRightOutside] = -65;
				motor[LauncherLeftInside] = -65;
				motor[LauncherRightInside] = -65;
			}

		}
	}

}

//function that allows for the control of the turntable
void ttable()
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
void drive(int frontLeft, int frontRight, int backLeft, int backRight)
{
	motor[FrontRightDrive] = frontRight;
	motor[BackRightDrive] =  backRight;
	motor[FrontLeftDrive] = frontLeft;
	motor[BackLeftDrive] =  backLeft;
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
