#include<Stepper.h>
// #include <Servo.h>

#define pin_prox 2
#define pin_in1 8
#define pin_in2 4
#define pin_in3 7
#define pin_in4 3
// #define pin_servo1 3
// #define pin_servo2 4
#define pin_trig 5
#define pin_echo 6

const float stepper_rev = 32;
const float gear_ratio = 64;
const float step_rev = stepper_rev * gear_ratio;

Stepper mystepper(stepper_rev, pin_in1, pin_in2, pin_in3, pin_in4);
long duration;
int distance;
int pos = 0;
int steps_req;
// Servo myservo1;
// Servo myservo2;

void setup()
{
   /*
   This Sections are only Executed once. This is used for initializing sensors and motors 
   */
   pinMode(pin_prox, INPUT);
   pinMode(pin_trig,OUTPUT);
   pinMode(pin_echo,INPUT);
   Serial.begin(9600);
  //  myservo1.attach(pin_servo1);
  //  myservo2.attach(pin_servo2);
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
      Serial.println("object detected non-metal");
      Serial.println(distance);
      Serial.println("Anti-Clockwise");
      steps_req = step_rev / 2;
      mystepper.setSpeed(1000);
      mystepper.step(steps_req);
      delay(2000);
      Serial.println("Clockwise");
      steps_req = -step_rev / 2;
      Serial.println("Val" + steps_req);
      mystepper.setSpeed(1000);
      mystepper.step(steps_req);
      delay(2000);




      // for (pos = 90; pos <= 135; pos += 1) {
      //   myservo1.write(pos);
      //   delay(1);
      // }
      // delay(3000);
      // for (pos = 135; pos >= 90; pos -= 1) {
      //   myservo1.write(pos);
      //   delay(1);
      // }
   // metal
   } else if (sensorValue_metal != 0) {
      Serial.println("object detected metal");
      // for (pos = 90; pos <= 135; pos += 1) {
      //   myservo2.write(pos);
      //   delay(1);
      // }
      // delay(3000);
      // for (pos = 135; pos >= 90; pos -= 1) {
      //   myservo2.write(pos);
      //   delay(1);
      // }
   } else {
      Serial.println("no metal or non-metal object detected");
   }
   delay(1000);
}
