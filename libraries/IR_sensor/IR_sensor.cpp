#include "Arduino.h"
#include "IR_sensor.h"

IR_sensor::IR_sensor(int _tcrtAL, int _tcrtAR, int _tcrtDL, int _tcrtDR){
	pinMode(_tcrtAL, INPUT);
	pinMode(_tcrtAR, INPUT);
	pinMode(_tcrtDL, INPUT);
	pinMode(_tcrtDR, INPUT);
	tcrtAL = _tcrtAL;
	tcrtAR = _tcrtAR;
	tcrtDL = _tcrtDL;
	tcrtDR = _tcrtDR;
}


IR_sensor::leftSensorA(void){
	return analogRead(tcrtAL);	
}

IR_sensor::rightSensorA(void){
	return analogRead(tcrtAR);
}

IR_sensor::leftSensorD(void){
	return analogRead(tcrtDL);
}

IR_sensor::rightSensorD(void){
	return analogRead(tcrtDR);
}

