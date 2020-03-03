#ifndef DC_motor_h
#define DC_motor_h

#include "Arduino.h"

class DC_motor{

private:
	// L91105 module motor control digital(PWM) pin
	int leftA;
	int leftB;
	int rightA;
	int rightB;
public:
	DC_motor(int _leftA, int _leftB, int _rightA, int _rightB);
	void rightSpeed(int speed);
	void leftSpeed(int speed);

};


#endif