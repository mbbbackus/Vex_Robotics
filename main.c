#pragma config(Sensor, in1,    Potent,         sensorPotentiometer)
#pragma config(Sensor, in3,    BaseGyro,       sensorGyro)
#pragma config(Sensor, dgtl1,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  LeftEncoder,    sensorQuadEncoder)
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

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

//the main program includes the code from these four files located within a central folder
#include "smartMotorLib\SmartMotorLib.c"
#include "field_centric_control.c"
#include "motor_functions.c"
#include "autonomous.c"

//Main user control function
//includes functions from the SmartMotorLib.c, field_centric_control.c and motor_functions.c
task usercontrol()
{
	SmartMotorRun();
	startTask(launcher);
	while(1 == 1)
	{
		mdrive();
		checkintake();
		turntable();
		calibrateButtons();

	}
}

//Initialize everything required before the autonomous starts
void pre_auton()
{
	bLCDBacklight = true;
	SmartMotorsInit();
	SmartMotorsAddPowerExtender(port5,port6,port7,port8);
	SmartMotorLinkMotors(port6,port2);
	SmartMotorLinkMotors(port6,port3);
	SmartMotorLinkMotors(port6,port5);
	//Ensure in future that gear ratio of high speed = 3.0
	SmartMotorsSetEncoderGearing(port6,3.0);
	SmartMotorPtcMonitorEnable();
	if(SensorValue[Potent] < 1000) setRed();
	else if(SensorValue[Potent] > 3000) setBlue();
	calcDirectionDifference();
	startTask(lcdtask);
}

//Run the autonomous function from the autonomous.c file
task autonomous()
{
	runAuton();
}
