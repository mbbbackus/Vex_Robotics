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
#pragma config(UART_Usage, UART2, uartVEXLCD, baudRate19200, IOPins, None, None)
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"

#include "motor_functions.c"
#include "smartMotorLib\SmartMotorLib.c"
#include "autonomous.c"

task lcdtask()
{
	float leftBackSpeed;
	float leftFrontSpeed;
	float rightBackSpeed;
	float rightFrontSpeed;

	float lb = 0;
	float rb = 0;
	float lf = 0;
	float rf = 0;

	while(1 == 1)
	{


		leftBackSpeed = SmartMotorGetSpeed(port2)   / 60 *12.56 ; //2r*pi * 60 seconds
		rightBackSpeed = SmartMotorGetSpeed(port3)  / 60 *12.56 ;
		leftFrontSpeed = SmartMotorGetSpeed(port6)  / 60 *12.56 ;
		rightFrontSpeed = SmartMotorGetSpeed(port5) / 60 *12.56 ;

		lb = lb + leftBackSpeed / 1000;
		rb = rb + rightBackSpeed / 1000;
		lf = lf + leftFrontSpeed / 1000;
		rf = rf + rightFrontSpeed / 1000;

		clearLCDLine(0);
		clearLCDLine(1);
		displayLCDString(0,0,"front:");
		displayNextLCDNumber(lf);
		displayNextLCDString(",");
		displayNextLCDNumber(rf);
		displayLCDString(1,0,"back:");
		displayNextLCDNumber(lb);
		displayNextLCDString(",");
		displayNextLCDNumber(rb);
		wait1Msec(1);
	}
}

task usercontrol()
{
	startTask(lcdtask);
	while(1 == 1)
	{
		mdrive();
		intake();
		launcher();
		turntable();
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
	SmartMotorRun();
}

task autonomous()
{
	runAuton();
}
