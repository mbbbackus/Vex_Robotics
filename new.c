#pragma config(Motor,  port1,           TurntableLeft, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           BackLeftDrive, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           BackRightDrive, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           LauncherLeft,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           FrontRightDrive, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           FrontLeftDrive, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           Intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           Outtake,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LauncherRight, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          TurntableRight, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	//Create "deadzone" variables. Adjust threshold value to increase/decrease deadzone
	int X2 = 0, Y1 = 0, X1 = 0, threshold = 15;

	//Loop Forever
	while(1 == 1)
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

		//Remote Control Commands
		motor[FrontRightDrive] = Y1 - X2 - X1;
		motor[BackRightDrive] =  Y1 - X2 + X1;
		motor[FrontLeftDrive] = Y1 + X2 + X1;
		motor[BackLeftDrive] =  Y1 + X2 - X1;

		//Intake
		if(vexRT[Btn6UXmtr2] == 0 && vexRT[Btn6DXmtr2] == 0){
			motor[Outtake] = 0;
			motor[Intake] = 0;
		}
		if(vexRT[Btn6UXmtr2] == 1){
			motor[Outtake] = -100;
			motor[Intake] = -100;
		}
		if(vexRT[Btn6DXmtr2] == 1){
			motor[Outtake] = 100;
			motor[Intake] = 100;
		}

		//Launcher
		if(vexRT[Btn7UXmtr2] == 0){
			motor[LauncherLeft] = 0;
			motor[LauncherRight] = 0;
		}
		if(vexRT[Btn7UXmtr2] == 1){
			motor[LauncherLeft] = -100;
			motor[LauncherRight] = -100;
		}

		//Turntable
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
}
