//launches preloaded balls from the starting square
void launch1(){
		for(int low = 0; low < 2; low++){
			grab(80);
			wait1Msec(900);
			grab(0);
			wait1Msec(1600);
			drive(70,70,70,70);
			wait1Msec(400);
			drive(0,0,0,0);
		}
	}
void launch2Blu(){
		for(int low = 0; low < 3; low++){
			turnLauncher(80);
			wait1Msec(100);
			turnLauncher(0);
			grab(80);
			wait1Msec(900);
			grab(0);
			wait1Msec(1600);
			drive(70,70,70,70);
			wait1Msec(400);
			drive(0,0,0,0);
		}
}
void launch2Red(){
	for(int low = 0; low < 3; low++){
			turnLauncher(-80);
			wait1Msec(100);
			turnLauncher(0);
			grab(80);
			wait1Msec(900);
			grab(0);
			wait1Msec(1600);
			drive(70,70,70,70);
			wait1Msec(400);
			drive(0,0,0,0);
		}
}
void runAutonBlu()
{
	//old autonomous
	/*launch(80);
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
	*/

	drive(80,80,80,80);
	wait1Msec(1000);
	drive(80,-80,80,-80);
	wait1Msec(450);
	drive(0,0,0,0);
	turnLauncher(80);
	wait1Msec(1600);
	turnLauncher(0);
	launch(65);
	wait1Msec(5000);
	drive(70,70,70,70);
	wait1Msec(300);
	drive(0,0,0,0);
	launch1();
	//drive(70,70,70,70);
	wait1Msec(500);
	//drive(0,0,0,0)
	launch2Blu();
	wait1Msec(500);
	//drive(70,70,70,70);
	launch2Blu();
	wait1Msec(500);
	drive(0,0,0,0);
}

void runAutonRed(){

	drive(80,80,80,80);
	wait1Msec(1000);
	drive(-80,80,-80,80);
	wait1Msec(450);
	drive(0,0,0,0);
	turnLauncher(-80);
	wait1Msec(1600);
	turnLauncher(0);
	launch(65);
	wait1Msec(5000);
	drive(70,70,70,70);
	wait1Msec(300);
	drive(0,0,0,0);
	launch1();
	//drive(70,70,70,70);
	wait1Msec(500);
	//drive(0,0,0,0)
	launch2Red();
	wait1Msec(500);
	//drive(70,70,70,70);
	launch2Red();
	wait1Msec(500);
	drive(0,0,0,0);
}

void runProgrammingSkills()
{
	launch(70);
	grab(80);

}
