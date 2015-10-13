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

#include "motor_functions.c"
#include "smartMotorLib\SmartMotorLib.c"
#include "autonomous.c"
#include "field_centric_control.c"

task usercontrol()
{
	SmartMotorRun();
	startTask(lcdtask);
	while(1 == 1)
	{
		mdrive();
		intake();
		launcher();
		turntable();
		dirButtons();
	}
}

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

	setLeftBlue();
	SensorValue[BaseGyro] = 0;
}

task autonomous()
{
	runAuton();
}
