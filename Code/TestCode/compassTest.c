#pragma config(Sensor, S2,     compass,        sensorI2CHiTechnicCompass)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
	while (true){
		writeDebugStreamLine("%d",SensorValue[compass]);
	}
}
