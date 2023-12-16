#define pin_t 2
void setup()
{
   pinMode(pin_t, INPUT);
   Serial.begin(9600);
}

void loop()
{
   int sensorValue = digitalRead(pin_t);
   if (sensorValue == 0) {
      Serial.println("object detected");
      delay(500);
   }
   else
   {
      Serial.println("no object");
      delay(500);
   }
}
