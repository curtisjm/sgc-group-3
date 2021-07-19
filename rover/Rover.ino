// code for rover

// include the servo library
#include <Servo.h>

// front distance sensor
const int trigPinFront = 0;
const int echoPinFront = 0;

// right distance sensor
const int trigPinRight = 11;
const int echoPinRight = 12;

// left distance censor
const int trigPinLeft = 5;
const int echoPinLeft = 6;

// initialize distance tracking variables
float frontDistance = 0;
float rightDistance = 0;
float leftDistance = 0;

// create a servo object
Servo servo;

// position when the servo is centered
int servoCenterPosition = 90;

void setup() {
	// trig pin outputs pulses of electricity
	// echo pin measures duration of pulses coming back
	pinMode(trigPinFront, OUTPUT);
	pinMode(echoPinFront, INPUT);
	pinMode(trigPinRight, OUTPUT);
	pinMode(echoPinRight, INPUT);
	pinMode(trigPinLeft, OUTPUT);
	pinMode(echoPinLeft, INPUT);

	// tell the servo object which pin the servo is plugged into
	servo.attach(9);
	// set servo to initial position
	servo.write(servoCenterPosition);

	// 115200 is for VS Code
	Serial.begin(115200);
	// change to 9600 if using Arduino IDE
	// Serial.begin(9600);
}

void loop() {
	// assign distances from front sensor to its variable
	frontDistance = getDistance(trigPinFront, echoPinFront);

	// output front distance to serial monitor
	Serial.println("Front: " + String(frontDistance));

	// once distance is less than our chosen threshold
	if(frontDistance < 50) {
		// check distances on either side of rover to see which direction has more room to travel towards
		rightDistance = getDistance(trigPinRight, echoPinRight);
		leftDistance = getDistance(trigPinLeft, echoPinLeft);

		// output side distances to serial monitor
		Serial.println("R: " + String(rightDistance) + "	L: " + String(leftDistance));

		// if there is more room on the left
		if(rightDistance < leftDistance) {
			servo.write(0);
			delay(1000);
			servo.write(servoCenterPosition);
		// if there is more room on the right
		} else {
			servo.write(180);
			delay(1000);
			servo.write(servoCenterPosition);
		}
	}
}

float getDistance(const int trigPin, const int echoPin) {
	// send an ultrasonic pulse that's 10ms long
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	// check how long it takes for the pulse to come back to the sensor
	float echoTime = pulseIn(echoPin, HIGH);
	// calculate the distance of the object that reflected the pulse
	float calculatedDistance = echoTime / 148.0;

	return calculatedDistance;
}