#ifndef IR_sensor_h
#define IR_sensor_h

#include "Arduino.h"

class IR_sensor{

private:
	//TCRT5000 IR module input analog pin
	int tcrtAL;
	int tcrtAR;
	int tcrtDL;
	int tcrtDR;
public:
	IR_sensor(int _tcrtAL, int _tcrtAR, int _tcrtDL, int _tcrtDR);
	int leftSensorA(void);
	int rightSensorA(void);
	int leftSensorD(void);
	int rightSensorD(void);
};

#endif