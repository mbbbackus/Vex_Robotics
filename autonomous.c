void runAuton()
{
	driveStraight(50);
	wait1Msec(1000);
	driveStraight(0);
	launch(80);
	wait1Msec(4000);
	grab(80);
	wait1Msec(8000);
	grab(0);
	launch(0);
}
