#pragma config(Sensor, in1,    Potent,         sensorPotentiometer)
#pragma config(Sensor, in3,    BaseGyro,       sensorGyro)
#pragma config(Sensor, dgtl1,  RightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  LeftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port1,           LauncherLeftInside, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           Intake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           BackLeftDrive, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           BackRightDrive, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           FrontRightDrive, tmotorVex393HighSpeed_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           FrontLeftDrive, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port7,           LauncherLeftOutside, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           LauncherRightOutside, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           Turntable,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          LauncherRightInside, tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

#include "smartMotorLib\SmartMotorLib.c"
#include "field_centric_control.c"
#include "motor_functions.c"
#include "autonomous.c"

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

void pre_auton()
{
	bLCDBacklight = true;
	SmartMotorsInit();
	SmartMotorsAddPowerExtender(port5,port6,port7,port8);
	SmartMotorLinkMotors(port6,port3);
	SmartMotorLinkMotors(port6,port4);
	SmartMotorLinkMotors(port6,port5);
	//Ensure in future that gear ratio of high speed = 3.0
	SmartMotorsSetEncoderGearing(port6,3.0);
	SmartMotorPtcMonitorEnable();
	if(SensorValue[Potent] < 1000) setRed();
	else if(SensorValue[Potent] > 3000) setBlue();
	calcDirectionDifference();
	startTask(lcdtask);
}

task autonomous()
{
	runAuton();
}
