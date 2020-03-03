#include <DC_motor.h>
#include <IR_sensor.h>

//모터 PWM 조종 핀 설정
//motor PWM pin setting DC_motor(leftMotorA, leftMotorB, rightMotorA, rightMotorB);
DC_motor DC_motor(5,6,9,10);

//적외선 센서 아날로그 입력 핀  설정
//IR sensor input pint setting IR_sensor(leftAnalogInput, rightAnalogInput ,leftDigitalInput, rightDigitalInput);
IR_sensor IR_sensor(0,1,13,13); //(Left Sensor)


// (검/흰)선 밝기 저장 변수
// a variable to contain (white/black) line brightness
int blackBrt=500;
int whiteBrt=30;

//현재 로봇이 어떤 모드인지 결정하는 상태변수 ex) state = 'r'이면 라인트레이싱 모드이다.
//a variable that indicates the robot's current state ex) if state='r' the robot is in line tracing mode
int state=0;

//버튼 입력의 상태를 알아보기 위한 변수
//a variable todetect button state
int lastButtonInput;
int presentButtonInput;

void testMotor(void);  //check motor
void testSensor(void);  //check sensor data in Serial monitor
void selfdrive(int black, int white, int margin);  //executes selfdriving mode(line tracing mode)

void setup() {
  Serial.begin(9600);

  //버튼과 PID스위치를 이용해 2진수 4자리 입력받기 위한 핀모드 세팅
  //setting pinmode for 16 possible inputs with PID switch and button
  pinMode(2,INPUT_PULLUP); //0 = 2^0
  pinMode(3,INPUT_PULLUP); //1 = 2^1
  pinMode(4,INPUT_PULLUP); //2 = 2^2
  pinMode(7,INPUT_PULLUP); //3 = 2^3
  pinMode(12,INPUT_PULLUP);//on

  //알림 신호 전달 핀
  //input comfirmed sound pin
  pinMode(11,INPUT_PULLUP);
}


void loop() {


//버튼과 PID스위치를 이용해 2진수 4자리 입력받기
//16 possible inputs with PID switch and button
//------------------------------------------------------------------------
  int menu[12]={'r','b','w','t',0,0,0,0,0,0,0,0};
  presentButtonInput = digitalRead(12);
  if(presentButtonInput==1 && lastButtonInput==0){  //if clicked
    state+=digitalRead(2)*1;  //gets the info from the PID swicth
    state+=digitalRead(3)*2;
    state+=digitalRead(4)*4;
    state+=digitalRead(7)*8;
    state=menu[state];  //gets the data from the array
    Serial.println(state);
    digitalWrite(11,HIGH);
    delay(1000);
    digitalWrite(11,LOW);
  }
//------------------------------------------------------------------------


  
  //'r' runs line follower
  //'t' diagonose test
  //'w' sets current brightness to white average
  //'b' sets current brightness to black average
  
  if(state == 'r'){
    selfdrive(blackBrt, whiteBrt, 100);
  }else if(state == 'b'){
    for(int i=0;i<10;i++){
      blackBrt+=IR_sensor.leftSensorA();
      blackBrt+=IR_sensor.rightSensorA();
    }blackBrt/=20;
    Serial.print("black brightness : ");
    Serial.println(blackBrt);
  }else if(state == 'w'){
    for(int i=0;i<10;i++){
      whiteBrt+=IR_sensor.leftSensorA();
      whiteBrt+=IR_sensor.rightSensorA();
    }whiteBrt/=20;
    Serial.print("white brightness : ");
    Serial.println(whiteBrt);
  }else if(state == 't'){
    Serial.println("test : ");
    testMotor();
    testSensor();
  }else{
    //확장 가능한 시스템
    //expandable system
  }
  state=0;

  //버튼의 마지막 입력신호 저장
  //saves button's last input
  //------------------------------------------------------------------------
  lastButtonInput = presentButtonInput;
  //------------------------------------------------------------------------

}



void testMotor(void){
  Serial.println("doing motor test...");
  DC_motor.rightSpeed(255);
  DC_motor.leftSpeed(255);
  delay(1000);
//  DC_motor.rightSpeed(-255);
//  DC_motor.leftSpeed(255);
  delay(1000);
  DC_motor.rightSpeed(0);
  DC_motor.leftSpeed(0);
}

void testSensor(void){
  Serial.print("Left Sensor Brightness : ");
  Serial.println(IR_sensor.leftSensorA());
  Serial.print("Right Sensor Brightness : ");
  Serial.println(IR_sensor.rightSensorA());
}


void selfdrive(int black, int white, int margin){
  
  Serial.println("self driving...");
  
  int ls,rs;
  int bmin,bmax,wmin,wmax;
  
  bmin = black - margin;
  bmax = black + margin;
  wmin = white - margin;
  wmax = white + margin;

  while(1){
    ls = IR_sensor.leftSensorA();
    rs = IR_sensor.rightSensorA();
    
//    Serial.print("\nwmin : ");
//    Serial.print(wmin);
//    Serial.print("\twmax : ");
//    Serial.println(wmax);
//    
//    Serial.print("bmin : ");
//    Serial.print(bmin);
//    Serial.print("\tbmax : ");
//    Serial.println(bmax);
//
//    Serial.print("left sensor : ");
//    Serial.print(ls);
//    Serial.print("\tright sensor : ");
//    Serial.println(rs);
        
    if( ((bmin<=ls)&&(ls<=bmax)) && ((bmin<=rs)&&(rs<=bmax)) ){       //left:black right:black
      DC_motor.leftSpeed(0);
      DC_motor.rightSpeed(0);
      Serial.println("stop");
      break;
    }else if( ((bmin<=ls)&&(ls<=bmax)) && ((wmin<=rs)&&(rs<=wmax)) ){ //left:black right:white
      while(1){
        ls = IR_sensor.leftSensorA();
        rs = IR_sensor.rightSensorA();
        DC_motor.leftSpeed(0);
        DC_motor.rightSpeed(225);
        if( ((wmin<=ls)&&(ls<=wmax)) && ((bmin<=rs)&&(rs<=bmax)) )break;
      }
      Serial.println("left");
    }else if(( ((wmin<=ls)&&(ls<=wmax)) && ((bmin<=rs)&&(rs<=bmax)) )){ //left:white right:black
      while(1){
        ls = IR_sensor.leftSensorA();
        rs = IR_sensor.rightSensorA();
        DC_motor.leftSpeed(225);
        DC_motor.rightSpeed(0);
        if( ((bmin<=ls)&&(ls<=bmax)) && ((wmin<=rs)&&(rs<=wmax)) )break;
      }
      Serial.println("right");
    }else if( ((wmin<=ls)&&(ls<=wmax)) && ((wmin<=rs)&&(rs<=wmax)) ){ //left:white right:white
      DC_motor.leftSpeed(225);
      DC_motor.rightSpeed(225);
      Serial.println("straight");
    }else{
      //more statements if you detect anything else
      Serial.println("sensor error");
      DC_motor.leftSpeed(0);
      DC_motor.rightSpeed(0);
    }
  }
}
