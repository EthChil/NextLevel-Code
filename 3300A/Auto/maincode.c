#pragma config(Sensor, port2,  LFLs,           sensorVexIQ_ColorGrayscale)
#pragma config(Sensor, port4,  Gyro,           sensorVexIQ_Gyro)
#pragma config(Sensor, port5,  RFLs,           sensorVexIQ_ColorGrayscale)
#pragma config(Sensor, port6,  MLs,            sensorVexIQ_ColorGrayscale)
#pragma config(Motor,  motor7,          RHerder,       tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor8,          RMotor,        tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor9,          LHerder,       tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor10,         LArm,          tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor11,         RArm,          tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor12,         LMotor,        tmotorVexIQ, PIDControl, reversed, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void waitForMotor(tMotor nMotorIndex) {

	while(getMotorZeroVelocity(nMotorIndex)){sleep(10);} //wait for the motor to start movisscanf

	while(!getMotorZeroVelocity(nMotorIndex)){sleep(10);} //wait for the motor to stop moving
	sleep(150);
}

// this code is made by Shawn and Max and Daniel and Even.
int calcThresh(tSensors sensor)
{
	int black = 1000;
	int white = -666;

	//StartTime is equal to nPGMtime
	//nPGMtime is now 2001
	//nPgmTime subtracted by startTime is 1 which is less than 5000
	//This while loop runs for 5 secs

	int startTime = nPgmTime;
	while(nPgmTime-startTime < 5000)
	{
		sleep(50);
		//Detects the brightes white
		if(getColorGrayscale(sensor) > white)
		{
			white = getColorGrayscale(sensor);
		}
		//Detects the darkest black
		if(getColorGrayscale(sensor) < black)
		{
			black = getColorGrayscale(sensor);
		}
	}
	//Calculates Threshold
	int Threshold = (white + black) /2;
	//Displays the treshold, white, and black
	displayVariableValues(line3,Threshold);
	displayVariableValues(line4,white);
	displayVariableValues(line5,black);
	//Wait 3 secs
	sleep(3000);
	//returns threshold
	return Threshold;
}

//function to stop at black line
void waitForBlack(tSensors sensor,int threshold)
{
	repeatUntil(getColorGrayscale(sensor) <=  threshold)
	{
		sleep(10);
	}
}

//function to stop at white line
void waitForWhite(tSensors sensor,int threshold)
{
	repeatUntil(getColorGrayscale(sensor) >=  threshold)
	{
		sleep(10);
	}
}

//function to stop after a few lines
void wait4lines(tSensors sens,int threshold ,int numLines){

	repeat(numLines)
	{
		waitForBlack(sens,threshold);
		waitForWhite(sens,threshold);
	}
}

//LMotorS > RMotorS track left
void lineFollow(tSensors sensor, int LSpeed, int RSpeed, int Thresh)
{
	if(getColorGrayscale(sensor) > Thresh)
	{
		setMotor(LMotor, LSpeed);
		setMotor(RMotor, RSpeed);
		}else{
		setMotor(LMotor, RSpeed);
		setMotor(RMotor, LSpeed);
	}
}

void doubleLineFollow(tSensors LSensor, tSensors RSensor, int LSpeed, int RSpeed, int ThreshLeft, int ThreshRight)
{
	if (getColorGrayscale(LSensor) > ThreshLeft && getColorGrayscale(RSensor) > ThreshRight){
		setMotor(LMotor, LSpeed);
		setMotorSpeed(RMotor, RSpeed);
	}
	if (getColorGrayscale(LSensor) < ThreshLeft && getColorGrayscale(RSensor) > ThreshRight){
		setMotorSpeed(LMotor, LSpeed);
		setMotorSpeed(RMotor, RSpeed);
	}
	if (getColorGrayscale(RSensor) < ThreshRight && getColorGrayscale(LSensor) > ThreshLeft){
		setMotorSpeed(LMotor, RSpeed);
		setMotorSpeed(RMotor, LSpeed);
	}
	if (getColorGrayscale(RSensor) < ThreshRight && getColorGrayscale(LSensor) < ThreshLeft){
		setMotorSpeed(LMotor, LSpeed);
		setMotorSpeed(RMotor, LSpeed);
	}
}

//1. get the lightsensor value
//2. check if that is whiter then our whitest white
//3. check if that is blacker than our blackest black
//Calcuate threshhold

//main task

task main()
{


	int MLsThresh = 50;
	int RFLsThresh = 80;
	int LFLsThresh = 80;

	displayTextLine(line1, "RFLs = %d", RFLsThresh);
	displayTextLine(line2, "MLs = %d", MLsThresh);


	resetGyro(Gyro);

	resetMotorEncoder(LMotor);
	resetMotorEncoder(RMotor);

	resetMotorEncoder(LArm);
	resetMotorEncoder(RArm);

	resetMotorEncoder(LHerder);
	resetMotorEncoder(RHerder);

	//MAIN PROGRAM

	//Herders up
	setMotorTarget(LHerder, 70, 20);
	setMotorTarget(RHerder, 70, 20);

	//Turn 60 degrees
	setMotor(LMotor, 80);
	setMotor(RMotor, -20);

	waitUntil(getGyrodegrees(Gyro) < -45);

	setMotor(LMotor, 80);
	setMotor(RMotor, -20);
	waitForBlack(RFLs, RFLsThresh);

	setMotor(LMotor, 50);
	setMotor(RMotor, 30);
	sleep (800);


	//Line counting



	while(getColorGrayscale(MLs) < MLsThresh){
		if(getColorGrayscale(RFLs) > RFLsThresh){
			setMotor(LMotor, 80);
			setMotor(RMotor, 20);
			}else{
			setMotor(LMotor, 30);
			setMotor(RMotor, 80);
		}
	}




	while(getColorGrayscale(MLs) > MLsThresh){
		if(getColorGrayscale(RFLs) > RFLsThresh){
			setMotor(LMotor, 60);
			setMotor(RMotor, 40);
			}else{
			setMotor(LMotor, 40);
			setMotor(RMotor, 60);
		}
	}
	setMotor(RMotor, 0);
	setMotor(LMotor, 0);
	resetMotorEncoder (RMotor);
	setMotorTarget(RMotor, 40, 60);
	waitForMotor(RMotor);
	setMotorTarget(RHerder, 0, 20);
	sleep(500);
	setMotorTarget(RMotor, 0, 60);
	waitForMotor(RMotor);

	//drive backwards
	setMotor( LMotor, -50);
	setMotor(RMotor, -50);
	sleep(1000);
	waitForBlack(MLs, MLsThresh);
	setMotor(RMotor, 0);
	setMotor(LMotor, 0);



	//grabing the 2nd set of hubs
	resetMotorEncoder(RMotor);
	setMotorTarget(RMotor, 190, 50);
	waitForMotor(RMotor);

	setMotor(RMotor, 50);
	setMotor(LMotor, 50);
	waitForBlack(LFLs,  LFLsThresh);

	clearTimer(T1);

	while(getTimerValue(T1) < 1000){
		if(getColorGrayscale(LFLs) > LFLsThresh){
			setMotor(LMotor, 90);
			setMotor(RMotor, 20);
			}else{
			setMotor(LMotor, 20);
			setMotor(RMotor, 40);

		}
	}

	setMotor(RMotor, -20);
	setMotor(LMotor, 50);
	setMotorTarget(LHerder, 50, 50);
	sleep(500);
	setMotor(LMotor, 0);
	setMotor(RMotor, 0);
	setMotorTarget(Lherder, 0, 70);
	sleep(1000);


	resetGyro(Gyro);

	//raise arm up before backing up into the wall
	resetMotorEncoder(LArm);
	resetMotorEncoder(RArm);
	setMotorTarget(LArm, 300, 50);
	setMotorTarget(RArm, 300, 50);
	sleep(2000)
}
	/*
	//turn 90 degree
	setMotor(LMotor, -50);
	setMotor(RMotor, 50);

	waitUntil(getGyrodegrees(Gyro) < 90);


}
/*



//Grabbing Hubs

setMotorTarget(LHerder, -70, 20);
setMotorTarget(RHerder, -70, 20);

/**/
//Turn 45 degrees then start waiting on the lightSensor
//Agressive line follow

//run threshold calculationcolorRedViolet

//Wait for tap sensor
//Start main program
