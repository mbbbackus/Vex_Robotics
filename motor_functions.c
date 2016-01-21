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

//Positive values rotate the launcher left, Negative values rotate the launcher right
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

void launchVel(int velocity){
	ClearTimer(T1);
	//higher starting value
	//shorter increments - checks
	//Set launcherpower as float
	/*vel_difference = rightFlywheelVelocity - velocity;
	if(vel_difference > 0){
		if(vel_difference > 200 ){
			launcherPower -=4;
			while(time1[T1] < 333) launch(launcherPower);
		}
		else if(vel_difference > 125 && vel_difference < 200 ){
			launcherPower -=3;
			while(time1[T1] < 400) launch(launcherPower);
		}
		else if(vel_difference > 66 && vel_difference < 125 ){
			launcherPower -=2;
			while(time1[T1] < 450) launch(launcherPower);
		}
		else if(vel_difference > 25 && vel_difference < 66 ){
			launcherPower -=1;
			while(time1[T1] < 1000) launch(launcherPower);
		}
		else{
			while(time1[T1] < 333) launch(launcherPower);
		}
	}
	else if(vel_difference < 0){
		if(vel_difference < -400 ){
			launcherPower +=3;
			while(time1[T1] < 333) launch(launcherPower);
		}
		else if(vel_difference < -200 && vel_difference > -400){
			launcherPower +=2;
			while(time1[T1] < 400) launch(launcherPower);
		}
		else if(vel_difference < -100 && vel_difference > -200){
			launcherPower +=1;
			while(time1[T1] < 500) launch(launcherPower);
		}
		else if(vel_difference < -25 && vel_difference > -100){
			launcherPower +=1;
			while(time1[T1] < 1000) launch(launcherPower);
		}
		else{
			while(time1[T1] < 333) launch(launcherPower);
		}
	}
	else launch(launcherPower);
	*/

	/*if(rightFlywheelVelocity > -800){
		launcherPower += 1;
	}
	else if(rightFlywheelVelocity < -850){
		launcherPower -=1;
	}
	while(time1[T1] < 333){
		motor[LauncherLeftOutside] =  -1 * launcherPower;
		motor[LauncherRightOutside] = -1 * launcherPower;
		motor[LauncherLeftInside] =   -1 * launcherPower;
		motor[LauncherRightInside] =  -1 * launcherPower;
	}*/
}

//function that controls the power of the launcher
//loops continuosly as the button is pressed
task launcher()
{
	// Highest -------> Lowest
	// 7U 7R 7D 7L 8U 8R 8D 8L
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
			ClearTimer(T1);
			while(time1[T1] < 1000) launch(55);
			while(vexRT[Btn7LXmtr2] == 1) launch(45);
		}
		//7U -- Medium
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 1 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 0 && vexRT[Btn8DXmtr2] == 0){
			//launchVel(550);
			ClearTimer(T1);
			while(time1[T1] < 1000) launch(65);
			while(vexRT[Btn7UXmtr2] == 1) launch(50);
		}
		//7R -- High
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 1 && vexRT[Btn7DXmtr2] == 0 && vexRT[Btn8DXmtr2] == 0){
			//launchVel(650);
			ClearTimer(T1);
			while(time1[T1] < 1000) launch(75);
			while(vexRT[Btn7RXmtr2] == 1) launch(60);
		}
		//7D -- Field-Centric
		if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 1 && vexRT[Btn8DXmtr2] == 0){
			//launchVel(800);
			ClearTimer(T1);
			while(time1[T1] < 1000) launch(85);
			while(vexRT[Btn7DXmtr2] == 1) launch(70);
		}
		/*if(vexRT[Btn7LXmtr2] == 0 && vexRT[Btn7UXmtr2] == 0 && vexRT[Btn7RXmtr2] == 0 && vexRT[Btn7DXmtr2] == 0 && vexRT[Btn8DXmtr2] == 1){
			motor[LauncherLeftOutside] = -1 * launcherPower;
			motor[LauncherRightOutside] = -1 * launcherPower;
			motor[LauncherLeftInside] = -1 * launcherPower;
			motor[LauncherRightInside] = -1 * launcherPower;
		}*/
	}

}
