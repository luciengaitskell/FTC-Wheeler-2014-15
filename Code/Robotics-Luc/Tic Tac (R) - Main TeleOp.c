#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Motor,  motorA,          liftA,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          liftB,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     rightF,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     rightB,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     leftF,         tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_2,     leftB,         tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "Transfer2.0.c"
#include "JoystickDriver.c"

task main()
{
	nMotorEncoder[liftA]=0;
	nMotorEncoder[liftB]=0;
	int joy_1y1;
	int joy_1y2;
	int joy_2y1;
	int dband=15;
	int liftLevels[2]={0, 2450};
	int encoderAverage;
	int armMovement=0;//0 = stopped, 1 = down, 2 = up
	float armGainSlow = 0.25;
	float armGainFast = 2.;
	float armGain = armGainFast;
	float driveGainSlow = 0.5;
	float driveGainFast = 1.;
	float driveGain = driveGainFast;
	int joyButtons1;
	int joyButtons2;
	int gainButton = 32;
	while (true){
		joyButtons1=joystick.joy1_Buttons;
		joyButtons2=joystick.joy2_Buttons;

		if (joyButtons1==gainButton){	//drive gain
			driveGain = driveGainSlow;
		}
		else{
			driveGain = driveGainFast;
		}

		if (joyButtons2==gainButton){	//arm gain
			armGain = armGainSlow;
			writeDebugStreamLine("arm slow");
		}
		else{
			armGain = armGainFast;
		}
		encoderAverage=(nMotorEncoder[liftA]+nMotorEncoder[liftB])/2;
		getJoystickSettings(joystick);
		joy_1y1=transfer_J_To_M(joystick.joy1_y1, dband, driveGain * 150./300.);//Driver Joy
		joy_1y2=transfer_J_To_M(joystick.joy1_y2, dband, driveGain * 150./300.);
		joy_2y1=transfer_J_To_M(joystick.joy2_y1, dband, armGain * 100./128.);//Gunner Joy - Arm
		//joy_2y2=transfer_J_To_M(joystick.joy2_y2, dband, 100./128.);
		//DRIVER//
		motor[leftF]=joy_1y1;
		motor[leftB]=joy_1y1;
		motor[rightF]=joy_1y2;
		motor[rightB]=joy_1y2;

		if (joy_2y1>0){//arm move up
			armMovement = 2;
		}
		else if (joy_2y1<0){//arm move down
			armMovement = 1;
		}
		else{//arm stopped
			armMovement = 0;
		}

		//Gunner//
		if (
			(encoderAverage<liftLevels[0] && armMovement == 1)// below lowest and going down
			|| (encoderAverage>liftLevels[sizeof(liftLevels)/sizeof(int)-1] && armMovement == 2) //above highest and going up
			|| armMovement == 0)//not moving
		{
				motor[liftA]=0;
				motor[liftB]=0;
		}
		else{
			// above lowest level and below highest level
			motor[liftA]=joy_2y1;
			motor[liftB]=joy_2y1;
		}
	}
}