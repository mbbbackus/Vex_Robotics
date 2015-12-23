//launches preloaded balls from the starting square
void runAuton()
{
	launch(57);
	//normally 75
	wait1Msec(5000);

	for(int low = 0; low < 3; low++){
		grab(80);
		wait1Msec(900);
		grab(0);
		wait1Msec(1600);
	}
	grab(80);
	wait1Msec(1500);
	grab(0);
	launch(0);

}
void runProgrammingSkills()
{
	launch(48);
	grab(80);
	//normally 75

	/*wait1Msec(5000);

	for(int low = 0; low < 3; low++){
		grab(80);
		wait1Msec(900);
		grab(0);
		wait1Msec(1600);
	}
	grab(80);
	wait1Msec(1500);
	grab(0);
	launch(0);
	drive(100, 100, 100, 100);
	wait1Msec(700);
	drive(100, -60, 100, -60);
	grab(80);
	wait1Msec(700);
	drive(0,0,0,0);
	turnLauncher(100);
	wait1Msec(500);
	turnLauncher(0);
	launch(46);
	wait1Msec(5000);
	for(int low = 0; low < 3; low++){
		grab(80);
		wait1Msec(900);
		grab(0);
		wait1Msec(1600);
	}
	grab(80);
	wait1Msec(1500);
	grab(0);
	launch(0);*/
}
