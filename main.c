#pragma config(Motor,  port1,           turntable,     tmotorVex393_HBridge, openLoop, encoderPort, None)
#pragma config(Motor,  port2,           drive_left_back, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port3,           drive_right_front, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port4,           left_launcher, tmotorVex393_HBridge, openLoop, encoderPort, None)
#pragma config(Motor,  port5,           left_intake,   tmotorVex393_HBridge, openLoop, encoderPort, None)
#pragma config(Motor,  port6,           right_intake,  tmotorVex393_HBridge, openLoop, encoderPort, None)
#pragma config(Motor,  port7,           right_launcher, tmotorVex393_HBridge, openLoop, encoderPort, None)
#pragma config(Motor,  port8,           drive_right_back, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port9,           drive_left_front, tmotorVex393HighSpeed_MC29, openLoop)
#pragma config(Motor,  port10,          outtake,       tmotorVex393_HBridge, openLoop, encoderPort, None)
#include "motor_functions.c"

task main()
{
		while(true)
		{
				mdrive();

		}


}
