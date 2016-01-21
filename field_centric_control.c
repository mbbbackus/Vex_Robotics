//displays values on the rear lcd screen for the field centric control program while the robot is on the field
int launcherPower = 50;
int leftFlywheelVelocity = 0;
int rightFlywheelVelocity = 0;

int rightDiff = 0;
int leftDiff = 0

/*task getVelocity()
{
	while(true)
	{
		leftDiff = SensorValue[RightLauncherEncoder];
		rightDiff = -1 * SensorValue[LeftLauncherEncoder];
		wait1Msec(50);
		SensorValue[RightLauncherEncoder] = 0;
		SensorValue[LeftLauncherEncoder] = 0;
	}
}*/

task lcdtask()
{

	bLCDBacklight = true;               // Turn on LCD Backlight
	string mainBattery, backupBattery;

	while(true)                         // An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);                 		// Clear line 1 (0) of the LCD
		clearLCDLine(1);                    // Clear line 2 (1) of the LCD

		//Display the Primary Robot battery voltage
		//displayLCDString(0, 0, "Primary: ");
		//sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
		//displayNextLCDString(mainBattery);

		//Display the Backup battery voltage
		//displayLCDString(1, 0, "Backup: ");
		//sprintf(backupBattery, "%1.2f%c", nAvgBatteryLevel/1000.0, 'V');    //Build the value to be displayed
		//displayNextLCDString(backupBattery);

		//displayLCDString(1, 0, "Pow: ");
		//sprintf(backupBattery, "-", launcherPower, "-");    //Build the value to be displayed
		displayLCDNumber(0, 0, launcherPower);
		displayLCDNumber(1, 0, rightFlywheelVelocity);

		//Short delay for the LCD refresh rate
		wait1Msec(100);
	}
}
