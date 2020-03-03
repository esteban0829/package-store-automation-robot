#include "Arduino.h"
#include "DC_motor.h"

DC_motor::DC_motor(int _leftA, int _leftB, int _rightA, int _rightB){
	pinMode(_leftA, OUTPUT);
	pinMode(_leftB, OUTPUT);
	pinMode(_rightA, OUTPUT);
	pinMode(_rightB, OUTPUT);
	leftA = _leftA;
	leftB = _leftB;
	rightA = _rightA;
	rightB = _rightB;
}

void DC_motor::leftSpeed(int speed){
	if(speed>=0){
		analogWrite(rightA, speed);  //왼쪽 전진 최고 속도
    	analogWrite(rightB, 0);      //왼쪽 전진 최고 속도
  	}else{
    	analogWrite(rightA, 0);      //왼쪽 후진 최고 속도
    	analogWrite(rightB, -speed); //왼쪽 후진 최고 속도
  	}
}

void DC_motor::rightSpeed(int speed){
	if(speed>=0){
	    analogWrite(leftA, speed);   //오른쪽 전진 최고 속도
	    analogWrite(leftB, 0);       //오른쪽 전진 최고 속도
	}else{
	    analogWrite(leftA, 0);       //오른쪽 후진 최고 속도
	    analogWrite(leftB, -speed);  //오른쪽 후진 최고 속도
	}
}