//drive base variables ------------
//shaft encoders - se
int se_backLeftLastVal;
int se_backLeftCurVal;
int se_backLeftDelta;

int se_frontLeftLastVal;
int se_frontLeftCurVal;
int se_frontLeftDelta;

int se_backRightLastVal;
int se_backRightCurVal;
int se_backRightDelta;

int se_frontRightLastVal;
int se_frontRightCurVal;
int se_frontRightDelta;

float se_right_distance;
float se_left_distance;

//integrated motor encoders - ime
int ime_backLeftLastVal;
int ime_backLeftCurVal;
int ime_backLeftDelta;

int ime_frontLeftLastVal;
int ime_frontLeftCurVal;
int ime_frontLeftDelta;

int ime_backRightLastVal;
int ime_backRightCurVal;
int ime_backRightDelta;

int ime_frontRightLastVal;
int ime_frontRightCurVal;
int ime_frontRightDelta;

float ime_right_distance;
float ime_left_distance;

float right_distance;
float left_distance;


//launcher variables ----------------
float launcherPowerVar; //power variable that can be updated

int highTorque = 50;
int highPower = 127;

//basketball terms used for shot distances
int layupPower = 50;
int jumpshotPower = 60;
int freethrowPower = 70;
int threepointerPower = 80;
int halfcourtpointPower = 90;
int fullcourtPower = 100;

//autononmous potentiometer variables -------------------
int redVal = 1000;
int blueVal = 3000;
