#include <Servo.h>

#define pin_t 2
#define led 3
#define servo_pin 4
#define pin_t2 5
#define trig 6
#define echo 7


long duration;
int distance;
Servo myservo;
int pos = 0; // initialize

void setup()
{
   pinMode(pin_t, INPUT);
   pinMode(pin_t2, INPUT);
   pinMode(led, OUTPUT);
   pinMode(trig,OUTPUT);
   pinMode(echo,INPUT);
   Serial.begin(9600);
   myservo.attach(servo_pin);
}
  
void loop()
{
   int sensorValue_plastic = digitalRead(pin_t);
   int sensorValue_metal = digitalRead(pin_t2);
   // Serial.println(sensorValue_plastic);
   digitalWrite(trig,LOW);
   delay(10);
   digitalWrite(trig,HIGH);
   delay(10);
   digitalWrite(trig,LOW);
   duration = pulseIn(echo,HIGH);
   distance = duration * 0.034 / 2;
   //Serial.print("Distance: ");
  // Serial.println(distance);

   // plastic
   if (distance <= 15 && sensorValue_metal != 0) {
      digitalWrite(3,HIGH);
      Serial.println("object detected plastic");
      // Serial.println(distance);
      for (pos = 90; pos <= 160; pos += 1) {
        myservo.write(pos);
        delay(1);
      }
      delay(3000);
      for (pos = 160; pos >= 90; pos -= 1) {
        myservo.write(pos);
        delay(1);
      }
      // delay(1000);
   }
   else
   {
      digitalWrite(3,LOW);
      // Serial.println("no object platic");
      // delay(500);
   }
   // metal
   if (sensorValue_metal == 0) {
      digitalWrite(3,HIGH); 
      Serial.println("object detected metal");
      for (pos = 90; pos >= 20; pos -= 1) {
        myservo.write(pos);
        delay(1);
      }
      delay(3000);
      for (pos = 20; pos <= 90; pos += 1) {
        myservo.write(pos);
        delay(1);
      }
      // delay(500);
   }
   else
   {
      digitalWrite(3,LOW);
      // Serial.println("no object metal");
      // delay(500);
   }
   delay(1000);
}
