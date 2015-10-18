void runAuton()
{
	driveStraight(50);
	launch(70);
	wait1Msec(1000);
	driveStraight(0);
	wait1Msec(2000);
	grab(100);
	wait1Msec(10000);
	grab(0);
	launch(0);
	wait1Msec(1000);
}
