//function controls the power of the intake
void powerIntake(int power)
{
	motor[Intake] = -power;
}

//Positive values drive the robot forward, Negative values drive it backward
void powerDriveBase(int left, int right)
{
	motor[FrontRightDrive] = right;
	motor[BackRightDrive] =  right;
	motor[FrontLeftDrive] = left;
	motor[BackLeftDrive] =  left;
}

//Positive values rotate the launcher left, Negative values rotate the launcher right
void powerTurntable(int power)
{
	motor[Turntable] = power;
}

//function that allows for the user to launch a ball at a given power
//potentially for use in autonomous
void powerLauncher(int power)
{
	motor[LauncherLeftOutside] =  power;
	motor[LauncherRightOutside] = power;
	motor[LauncherLeftInside] =   power;
	motor[LauncherRightInside] =  power;
}

//basic drive function
void driveBase_listener()
{
	//Remote Control Commands
	motor[FrontRightDrive] = vexRT[Ch2];
	motor[BackRightDrive] = vexRT[Ch2];
	motor[FrontLeftDrive] = vexRT[Ch3];
	motor[BackLeftDrive] =  vexRT[Ch3];
}

//function that controls the intake
//loops continuously as the button is pressed
void intake_listener() // 1 forward, 0 backward
{

	//if button 6U (onCNTRL2) is pressed, run intake and outtake at -100
	if(vexRT[Btn6U] == 1 || vexRT[Btn6UXmtr2] == 1){
		motor[Intake] = -100;
	}
	//if button 6D (onCNTRL2) is pressed, run intake and outtake at 100
	else
		if(vexRT[Btn6D] == 1 || vexRT[Btn6DXmtr2] == 1){
		motor[Intake] = 100;
	}
	//in any other situation, dont run
	else {
		motor[Intake] = 0;
	}
}


//function that allows for the control of the turntable
void turntable_listener()
{
	motor[Turntable] = vexRT[Ch1Xmtr2];
}

//Values:
//low  - 55,45
//mid  - 65,50
//high - 75,60
//full - 85,70

task launcher_listener()
{
	while(1==1){
		if(vexRT[Btn8U] == 1){
 			launcherPower += 1;
			wait1Msec(500);
		}
		else if(vexRT[Btn8D] == 1){
			launcherPower -= 1;
			wait1Msec(500);
		}
		//None pressed
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 0 && vexRT[Btn8DXmtr2] == 0){
			motor[LauncherLeftOutside] =  0;
			motor[LauncherRightOutside] = 0;
			motor[LauncherLeftInside] =   0;
			motor[LauncherRightInside] =  0;
			launcherPower = 55;
		}
		//7L -- Lowest
		if(vexRT[Btn7LXmtr2] == 1 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 0 && vexRT[Btn8DXmtr2] == 0){
			//launchVel(475);
			clearTimer(T1);
			while(time1[T1] < 1000) powerLauncher(55);
			while(vexRT[Btn7LXmtr2] == 1) powerLauncher(45);
		}
		//7U -- Medium
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 1 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 0 && vexRT[Btn8DXmtr2] == 0){
			//launchVel(550);
			clearTimer(T1);
			while(time1[T1] < 1000) powerLauncher(65);
			while(vexRT[Btn7UXmtr2] == 1) powerLauncher(50);
		}
		//7R -- High
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 1 && vexRT[Btn7DXmtr2] == 0 && vexRT[Btn8DXmtr2] == 0){
			//launchVel(650);
			clearTimer(T1);
			while(time1[T1] < 1000) powerLauncher(75);
			while(vexRT[Btn7RXmtr2] == 1) powerLauncher(60);
		}
		//7D -- Field-Centric
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 1 && vexRT[Btn8DXmtr2] == 0){
			//launchVel(800);
			clearTimer(T1);
			while(time1[T1] < 1000) powerLauncher(85);
			while(vexRT[Btn7DXmtr2] == 1) powerLauncher(70);
		}
	}
}
