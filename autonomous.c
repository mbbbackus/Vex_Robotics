void runAuton()
{
	wait1Msec(2000);
	driveStraight(100);
	launch(60);
	wait1Msec(4000);
	driveStraight(0);
	wait1Msec(500);
	strafe(0);
	grab(100);
	wait1Msec(8000);
	grab(0);
	launch(0);
	wait1Msec(1000);
}
