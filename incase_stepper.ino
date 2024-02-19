#include<Stepper.h>
const float stepper_rev = 32;
const float gear_ratio = 64;
const float step_rev = stepper_rev * gear_ratio;


int steps_req;

Stepper mystepper(stepper_rev, 2, 4, 3, 5);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // digitalWrite()

  Serial.println("Anti-Clockwise");
  steps_req = step_rev / 2;
  mystepper.setSpeed(900);
  mystepper.step(steps_req);
  delay(5000);
  Serial.println("Clockwise");
  steps_req = -step_rev / 2;
  Serial.println("Val" + steps_req);
  mystepper.setSpeed(900);
  mystepper.step(steps_req);
  delay(5000);
}
