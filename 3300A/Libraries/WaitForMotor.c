#pragma config(Motor,  motor1,          LMotor,        tmotorVexIQ, PIDControl, driveLeft, encoder)
#pragma config(Motor,  motor6,          RMotor,        tmotorVexIQ, PIDControl, reversed, driveRight, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void waitForMotor(tMotor nMotorIndex) {

	while(getMotorZeroVelocity(nMotorIndex)){sleep(10);} //wait for the motor to start moving

	while(!getMotorZeroVelocity(nMotorIndex)){sleep(10);} //wait for the motor to stop moving
}


task main()
{
	setMotorTarget(LMotor,1000,50);
	setMotorTarget(RMotor,1000,50);
	waitForMotor(LMotor);
	setMotorTarget(LMotor,0,50);
	setMotorTarget(RMotor,0,50);
	waitForMotor(LMotor);
	stopAllMotors();
}
