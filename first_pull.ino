#include <Servo.h>

#define pin_t 2
#define led 3
#define servo_pin 4
#define pin_t2 5

Servo myservo;
int pos = 0; // initialize

void setup()
{
   pinMode(pin_t, INPUT);
   pinMode(pin_t2, INPUT);
   Serial.begin(9600);
   pinMode(led, OUTPUT);
   myservo.attach(servo_pin);
}
  
void loop()
{
   int sensorValue_plastic = digitalRead(pin_t);
   int sensorValue_metal = digitalRead(pin_t2);
   Serial.println(sensorValue_plastic);
   // plastic
   if (sensorValue_plastic != 0) {
      digitalWrite(3,HIGH);
      Serial.println(pos + " true");
      for (pos = 90; pos <= 160; pos += 1) {
        myservo.write(pos);
        delay(1);
      }
      delay(3000);
      for (pos = 160; pos >= 90; pos -= 1) {
        myservo.write(pos);
        delay(1);
      }
      Serial.println("object detected plastic");
      delay(500);
   }
   else
   {
      digitalWrite(3,LOW);
      Serial.println("no object platic");
      delay(500);
   }
   // metal
   if (sensorValue_metal == 0) {
      digitalWrite(3,HIGH);
      for (pos = 90; pos >= 20; pos -= 1) {
        myservo.write(pos);
        delay(1);
      }
      delay(3000);
      for (pos = 20; pos <= 90; pos += 1) {
        myservo.write(pos);
        delay(1);
      }
      Serial.println("object detected metal");
      delay(500);
   }
   else
   {
      digitalWrite(3,LOW);
      Serial.println("no object metal");
      delay(500);
   }
}
