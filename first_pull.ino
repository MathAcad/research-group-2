#include <Servo.h>

// define pin
#define led 3
#define servo_pin 4
#define pin_t2 5
#define trig 6
#define echo 7

// define and initialize variables
long duration;
int distance;
int pos = 0;

// call servo service
Servo myservo;


void setup()
{
	// attach modes
	pinMode(pin_t2, INPUT);
	pinMode(led, OUTPUT);
	pinMode(trig,OUTPUT);
	pinMode(echo,INPUT);
	myservo.attach(servo_pin);
	
	// Sets the data rate in bits per second (baud) for serial data transmission. in our case (9600)
	Serial.begin(9600);
}
	
void loop()
{
	// reads the sensor's state
	int sensorValue_metal = digitalRead(pin_t2);
	
	// initialize the trig first
	digitalWrite(trig,LOW);
	delay(10);
	
	// sets the trig on HIGH state for 10ms
	digitalWrite(trig,HIGH);
	delay(10);
	digitalWrite(trig,LOW);
	
	// get the duration from pulseIn() function, takes 2 args.
	duration = pulseIn(echo,HIGH);
	// calculation of speed of sound
	distance = duration * 0.034 / 2;

	// plastic section
	// condition: if the value of distance calculated earlier is lower than 11, and metal sensor returns non-zero integer, then the object is PLASTIC
	if (distance <= 11 && sensorValue_metal != 0) {
		digitalWrite(led, HIGH);
		Serial.println("object detected plastic");
		for (pos = 90; pos <= 160; pos += 1) {
			myservo.write(pos);
			delay(1);
		}
		delay(3000);
		for (pos = 160; pos >= 90; pos -= 1) {
			myservo.write(pos);
			delay(1);
		}
	}
	else
	{
		// sets the bulb off
		digitalWrite(led, LOW);
	}
	// metal section
	// condition: if the value of metal sensor is zero, means the obstacle is Metal
	if (sensorValue_metal == 0) {
		digitalWrite(led, HIGH); 
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
	}
	else
	{
		// sets the bulb off
		digitalWrite(led, LOW);
	}
	// add a delay, for next decision
	delay(2000);
}
