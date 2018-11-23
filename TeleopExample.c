#pragma config(Motor,  motor1,          LMotor,        tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor2,          Strafe,        tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor3,          RHerder,       tmotorVexIQ, PIDControl, reversed, encoder)
#pragma config(Motor,  motor4,          LHerder,       tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor5,          Arm,        tmotorVexIQ, PIDControl, encoder)
#pragma config(Motor,  motor6,          RMotor,           tmotorVexIQ, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
//CHA Vertical Travel
//CHB Yaw
//CHC Horizontal Travel
//CHD Arm

	while(true){
		//Grab the joystick values and save them into variables
		//The float type means floating point or decimal
		float LPitch = getJoystickValue(ChA);
		float LYaw = getJoystickValue(ChB);
		float RYaw = getJoystickValue(ChC);
		float RPitch = getJoystickValue(ChD);

		//check if controller value is small enough
		//if it is make it zero
		//this accounts for the poor build of certain controllers minimizing drift
		//abs will remove the negative sign from a number
		if(abs(LPitch) < 0.1) LPitch = 0;
		if(abs(LYaw) < 0.1) LYaw = 0;
		if(abs(RPitch) < 0.1) RPitch = 0;
		if(abs(RYaw) < 0.1) RYaw = 0;

		//Set the drive motors
		//this is an arcade format
		setMotor(LMotor, LPitch-LYaw);
		setMotor(RMotor, LPitch+LYaw);

		//Set the arm and strafe motors
		setMotor(Arm, RPitch);
		setMotor(Strafe, RYaw);

		//TODO: add the herders
		//TODO: add safety
	}
}
