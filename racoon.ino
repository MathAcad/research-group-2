#include<Stepper.h>

#define pin_prox 2
#define pin_in1 8
#define pin_in2 4
#define pin_in3 7
#define pin_in4 3
#define pin_trig 5
#define pin_echo 6

const float stepper_rev = 32;
const float gear_ratio = 10;
const float step_rev = 2048;
// const float step_rev = stepper_rev * gear_ratio;

Stepper mystepper(stepper_rev, pin_in1, pin_in2, pin_in3, pin_in4);
long duration;
int distance;
int pos = 0;
int steps_req;

void setup()
{
   /*
   This Sections are only Executed once. This is used for initializing sensors and motors 
   */
   pinMode(pin_prox, INPUT);
   pinMode(pin_trig,OUTPUT);
   pinMode(pin_echo,INPUT);
   Serial.begin(9600);
}
  
void loop()
{
   int sensorValue_metal = digitalRead(pin_prox);
   digitalWrite(pin_trig,LOW);
   delay(10);
   digitalWrite(pin_trig,HIGH);
   delay(10);
   digitalWrite(pin_trig,LOW);
   duration = pulseIn(pin_echo,HIGH);
   distance = duration * 0.034 / 2;

   // non-metal
   if (distance <= 9 && sensorValue_metal == 0) {
      steps_req = 0;
      Serial.println("object detected non-metal");
      Serial.println(distance);
      Serial.println("Anti-Clockwise");
      steps_req = step_rev / 2;
      mystepper.setSpeed(600);
      mystepper.step(steps_req);
      delay(1000);
      Serial.println("Clockwise");
      steps_req = -290;
      // steps_req = -step_rev / 2;
      // Serial.println("Clockwise" + steps_req);
      mystepper.setSpeed(600);
      mystepper.step(steps_req);
      // int steps_req = 0;
   // metal
   } else if (sensorValue_metal != 0) {
      steps_req = 0;
      Serial.println("object detected metal");
      Serial.println("Clockwise");
      // steps_req = -step_rev / 2;
      steps_req = -285;
      
      mystepper.setSpeed(600);
      mystepper.step(steps_req);
      delay(1000);
      Serial.println("Anti-Clockwise");
      steps_req = 310;
      // steps_req = step_rev / 2;
      mystepper.setSpeed(600);
      mystepper.step(steps_req);
      // int steps_req = 0;
   } else {
      Serial.println("no metal or non-metal object detected");
   }
   delay(500);
}
