//launches preloaded balls from the starting square
void launch1(){
		for(int low = 0; low < 2; low++){
			powerIntake(80);
			wait1Msec(900);
			powerIntake(0);
			wait1Msec(1600);
			powerDriveBase(70,70);
			wait1Msec(400);
			powerDriveBase(0,0);
		}
	}
void launch2Blu(){
		for(int low = 0; low < 3; low++){
			powerTurntable(80);
			wait1Msec(100);
			powerTurntable(0);
			powerIntake(80);
			wait1Msec(900);
			powerIntake(0);
			wait1Msec(1600);
			powerDriveBase(70,70);
			wait1Msec(400);
			powerDriveBase(0,0);
		}
}
void launch2Red(){
	for(int low = 0; low < 3; low++){
			powerTurntable(-80);
			wait1Msec(100);
			powerTurntable(0);
			powerIntake(80);
			wait1Msec(900);
			powerIntake(0);
			wait1Msec(1600);
			powerDriveBase(70,70);
			wait1Msec(400);
			powerDriveBase(0,0);
		}
}
void runAutonBlu()
{
	powerDriveBase(80,80);
	wait1Msec(1000);
	powerDriveBase(80,-80);
	wait1Msec(450);
	powerDriveBase(0,0);
	powerTurntable(80);
	wait1Msec(1600);
	powerTurntable(0);
	powerLauncher(65);
	wait1Msec(5000);
	powerDriveBase(70,70);
	wait1Msec(300);
	powerDriveBase(0,0);
	launch1();
	wait1Msec(500);
	launch2Blu();
	wait1Msec(500);
	launch2Blu();
	wait1Msec(500);
	powerDriveBase(0,0);
}

void runAutonRed(){

	powerDriveBase(80,80);
	wait1Msec(1000);
	powerDriveBase(-80,80);
	wait1Msec(450);
	powerDriveBase(0,0);
	powerTurntable(-80);
	wait1Msec(1600);
	powerTurntable(0);
	powerLauncher(65);
	wait1Msec(5000);
	powerDriveBase(70,70);
	wait1Msec(300);
	powerDriveBase(0,0);
	launch1();
	wait1Msec(500);
	launch2Red();
	wait1Msec(500);
	launch2Red();
	wait1Msec(500);
	powerDriveBase(0,0);
}

void runProgrammingSkills()
{
	powerLauncher(70);
	powerIntake(80);

}
