#include <Servo.h>

#define pin_t 2
#define led 3
#define servo_pin 4

Servo myservo;
int pos = 0; // initialize

void setup()
{
   pinMode(pin_t, INPUT);
   Serial.begin(9600);
   pinMode(led, OUTPUT);
   myservo.attach(servo_pin);
}
  
void loop()
{
   int sensorValue = digitalRead(pin_t);
   Serial.println(sensorValue);
   if (sensorValue == 0) {
      digitalWrite(3,HIGH);
      for (pos = 0; pos <= 180; pos += 1) {
        myservo.write(pos);
        delay(1);
      }
      Serial.println("object detected");
      delay(500);
   }
   else
   {
      digitalWrite(3,LOW);
      for (pos = 180; pos >= 0; pos -= 1) {
        myservo.write(pos);
        delay(1);
      }
      Serial.println("no object");
      delay(500);
   }
}
