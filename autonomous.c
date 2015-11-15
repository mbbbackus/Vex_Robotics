//launches preloaded balls from the starting square
void runAuton()
{
	launch(60);
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
