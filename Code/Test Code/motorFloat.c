#pragma config(Motor,  motorA,          motor1,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          motor2,        tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          motor3,        tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	bFloatDuringInactiveMotorPWM = true;
	motor[motor1]=0;
	motor[motor2]=0;
	motor[motor3]=0;
	while (true){
		if (nNxtButtonPressed == 3){
			break;
		}
	}
	bFloatDuringInactiveMotorPWM = false;
}
