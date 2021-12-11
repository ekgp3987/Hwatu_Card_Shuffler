#include <SoftwareSerial.h> 
int state = 0; // 1 is off 2 is on, 3 is ready
int infrared = 3;
int infrared_val = 0;
int cds_val = 0;
char data;

#define IN1 12
#define IN2 13
#define IN3 11
#define IN4 10
#define IN5 4
#define IN6 8
#define EN1 9
#define EN2 5
#define EN3 6
#define cds A1
#define infrared 3
#define __MEGA2560__ 0                   //0: Uno, 1: Mega 2560
#define White 7
#if __MEGA2560__
#define mySerial Serial3
#else
int blueTx=2;   
int blueRx=3;   
SoftwareSerial mySerial(blueTx, blueRx);
#endif

#define BAUDRATE 9600                 //select 9600 or 115200 w.r.t module

void setup() 
{
  Serial.begin(BAUDRATE);   
  mySerial.begin(BAUDRATE);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(IN5,OUTPUT);
  pinMode(IN6,OUTPUT);
  pinMode(EN1,OUTPUT);
  pinMode(EN2,OUTPUT);
  pinMode(EN3,OUTPUT);
  pinMode(White,OUTPUT);
  pinMode(infrared, INPUT);
  pinMode(cds, INPUT);
}
void loop()
{
  infrared_val = digitalRead(infrared);
  cds_val = analogRead(cds);       
  if (mySerial.available()) {      
    //Serial.write(mySerial.read());
    data = (char)mySerial.read();
    Serial.println(data);
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
    if(data == '1'){
      state = 1;
    }if(data == '2'){
      state = 2;
    }if(data == '3'){
      state = 3;
    }if(data == '4'){
      state = 4;
    }if(data == '5'){
      state = 5;
    }
      
    if (state == 2) {
      //motor on
      digitalWrite(White,HIGH);
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      analogWrite(EN1,255);
      delay(1000);
      data = 3;
      //if 조도가 올라가면 state= 3
      //if 적외선 check되면 state =3
    }
    else if ( state == 1) {
      digitalWrite(White,LOW);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      analogWrite(EN1,0);
      analogWrite(EN2,0);
      //motor off
    } else if (state == 3) {
      digitalWrite(White,LOW);
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      analogWrite(EN1,127);
      delay(1000);
      data =2;
      //motor UP
    } else if (state == 4) {
      digitalWrite(White,LOW);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      analogWrite(EN1,110);
      delay(1000);
      data =4;
      //motor UP
    }else if (state == 5) {
      digitalWrite(White,LOW);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      analogWrite(EN2,200);
      delay(1000);
      data =5;
      //motor UP
    }
    //if ((infrared_val == HIGH) && (cds_val > 100) && (state = 3)){
      //data =1;
    //}
}
