#pragma config(Sensor, port9,  Gyro,           sensorVexIQ_Gyro)
#pragma config(Sensor, port10, TouchSensor,    sensorVexIQ_LED)
#pragma config(Sensor, port11, MLs,            sensorVexIQ_ColorGrayscale)
#pragma config(Sensor, port12, RFLs,           sensorVexIQ_ColorGrayscale)
#pragma config(Motor,  motor1,          LHerder,       tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor2,          LArm,          tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor3,          RArm,          tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor4,          RMotor,        tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor5,          RHerder,       tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor6,          LMotor,        tmotorVexIQ, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//PORT INFOMATION
//MOTORS

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
//variable
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
///function to stop at white line
void waitForWhite(tSensors sensor,int threshold)
{
	repeatUntil(getColorGrayscale(sensor) >=  threshold)
	{
		sleep(10);
	}
}
//function to stop after a few lines
void wait4lines(tSensors sens,int threshold ,int numLines)
{
  repeat(numLines)
  {
	  waitForBlack(sens,threshold);
	  waitForWhite(sens,threshold);
  }
}

//1. get the lightsensor value
//2. check if that is whiter then our whitest white
//3. check if that is blacker than our blackest black
//Calcuate threshhold

//main task
task main()
{

	//INIT
	//Wait for sensors to start up
	writeDebugStreamLine("%d", getColorGrayscale(lightSensor));
	sleep(1000);

	//Tap touch sensor to start threshold calculation
	//run threshold calculation
	//print thresholds on the screen

	//Wait for tap sensor
	//Start main program
  //variable

}
