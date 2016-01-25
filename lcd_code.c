task lcdtask()
{
	bLCDBacklight = true;               // Turn on LCD Backlight
	while(true)                         // An infinite loop to keep the program running until you terminate it
	{
		clearLCDLine(0);                 		// Clear line 1 (0) of the LCD
		clearLCDLine(1);                    // Clear line 2 (1) of the LCD
		displayLCDNumber(0, 0, launcherPowerVar);
		wait1Msec(100);
	}
}
