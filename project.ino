// Practical Research 2

// include library
// servo motor library
#include <Servo.h>

// Plastic bin pin definitions
#define redpin 5
#define bluepin 6
#define greenpin 7
#define plasticsensor A0
#define metalsensor A1
#define IR_plastic A3

// Metal bin pin definitions
#define redpin_M 8
#define bluepin_M 9
#define greenpin_M 10
#define metalsensor_M A2
#define IR_metal A3

// Create servo object to control a servo on plastic bin
Servo myservo;
// create servo object to control a servo on metal bin
Servo myservo_M;


// deafult servo position of plastic bin
int pos = ""; // 165
// deafult servo position of metal bin
int pos_M = ""; //158


void setup() {
	// Attaches the plastic bin servo on pin 11 to the servo object
	myservo.attach(11);
	
	// Attaches the metal bin servo on pin 12 to the servo object
	myservo_M.attach(12);
	
	// RGB LED on plastic bin
	pinMode(redpin,OUTPUT);
	pinMode(bluepin,OUTPUT);
	pinMode(greenpin,OUTPUT);

	// RGB LED on metal bin
	pinMode(redpin_M,OUTPUT);
	pinMode(bluepin_M,OUTPUT);
	pinMode(greenpin_M,OUTPUT);
	
	// Create sensor values in pull up condition
	pinMode(plasticsensor,INPUT_PULLUP);
	pinMode(metalsensor,INPUT_PULLUP);
	pinMode(metalsensor_M,INPUT_PULLUP);
	
	// Activate IR sensor
	pinMode(IR_plastic,INPUT);
	pinMode(IR_metal,INPUT);
	
	// Start serial monitor
	Serial.begin(9600);
	
	//Set RGB LED on deafult vaues (white)
	analogWrite(redpin,255);
	analogWrite(bluepin,255);
	analogWrite(greenpin,255);
	analogWrite(redpin_M,255);
	analogWrite(bluepin_M,255);
	analogWrite(greenpin_M,255);
}


void loop() {
	int sensor_read_plastic = digitalRead(plasticsensor);
	int sensor_read_metal = digitalRead(metalsensor);
	int sensor_read_metaletal2 = digitalRead(metalsensor_M);
	int sensor_read_IR_plastic = digitalRead(IR_plastic);
	int sensor_read_IR_metal = digitalRead(IR_metal);
	Serial.println("plastic sensor");
	Serial.println(sensor_read_plastic);
	Serial.println("metal sensor");
	Serial.println(sensor_read_metal);
	Serial.println(sensor_read_metaletal2);
	
	// Check if the trash bin is full
	// Plastic bin
	if(sensor_read_IR_plastic == 1) {
		analogWrite(redpin,255);
		analogWrite(bluepin,0);
		analogWrite(greenpin,0);
	}
	
	// Metal bin
	if(sensor_read_IR_metal == 1){
		analogWrite(redpin_M,255);
		analogWrite(bluepin_M,0);
		analogWrite(greenpin_M,0);
	}
	
	// plastic bin
	// might be wrong condition
	if((sensor_read_plastic == 0) && (sensor_read_metal != 1)){
		// (160° to 0°)
		// tweak the ranging pos
		for (pos = 160; pos >= 90; pos -= 1) {
			// in steps of 1 degree
			// tell servo to go to position in variable 'pos'
			myservo.write(pos);
			// waits 1ms for the servo to reach the position
			delay(1);
		}
		analogWrite(redpin,255);
		analogWrite(bluepin,0);
		analogWrite(greenpin,255);
		delay(2500);
		// (90° to 160°) unsure
		// tweak the ranging pos
		for (pos = ""; pos <= ""; pos += 1) {
			// tell servo to go to position in variable 'pos'
			myservo.write(pos);
			// waits 1ms for the servo to reach the position
			delay(1);
		}
		analogWrite(redpin,0);
		analogWrite(bluepin,0);
		analogWrite(greenpin,0);
	}
	else {
		// keep the door close
		myservo.write(pos); 
		
		analogWrite(redpin,255);
		analogWrite(bluepin,255);
		analogWrite(greenpin,255);
	
	}
	
	//metal bin
	if(sensor_read_metaletal2 == 1){
		// (160° to 90°)
		// tweak it
		for (pos_M = ""; pos_M >= ""; pos_M -= 1) {
			// in steps of 1 degree
			// tell servo to go to position in variable 'pos'
			myservo_M.write(pos_M);
			// waits 1ms for the servo to reach the position
			delay(1);
		}
		analogWrite(redpin_M,255);
		analogWrite(bluepin_M,0);
		analogWrite(greenpin_M,255);
		delay(2500);
		// 90° to 160°
		// tweak it
		for (pos_M = 90; pos_M <= 160; pos_M += 1) {
			// tell servo to go to position in variable 'pos'
			myservo_M.write(pos_M);
			// waits 1ms for the servo to reach the position
			delay(1);
	
		}
		analogWrite(redpin_M,0);
		analogWrite(bluepin_M,0);
		analogWrite(greenpin_M,0);
	}
	else {
		// keep the door close
		myservo_M.write(pos_M); 
		
		analogWrite(redpin_M,255);
		analogWrite(bluepin_M,255);
		analogWrite(greenpin_M,255);
	}
}
