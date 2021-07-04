// testing the distance censors to check accuracy and how to interface with multiple of them

// right distance sensor
const int trigPinRight = 11;
const int echoPinRight = 12;

// left distance censor
const int trigPinLeft = 5;
const int echoPinLeft = 6;

// initialize distance tracking variables
float rightDistance = 0;
float leftDistance = 0;

void setup() {
	// trig pin outputs pulses of electricity
	// echo pin measures duration of pulses coming back
	pinMode(trigPinRight, OUTPUT);
	pinMode(echoPinRight, INPUT);
	pinMode(trigPinLeft, OUTPUT);
	pinMode(echoPinLeft, INPUT);

	// change to 9600 if using Arduino IDE
	// 115200 is for VS Code
	Serial.begin(115200);
}

void loop() {
	// assign distances from each sensor to their respective variables
	rightDistance = getDistance(trigPinRight, echoPinRight);
	leftDistance = getDistance(trigPinLeft, echoPinLeft);

	// output distances to serial monitor
	Serial.println("R: " + String(rightDistance) + "	L: " + String(leftDistance));

	// wait 50ms between readings
	delay(50);
}

float getDistance(const int trigPin, const int echoPin) {
	// variable to store the time it takes for a ping to bounce off an object
	float echoTime;
	float calculatedDistance;

	// send out an ultrasonic pulse that's 10ms long
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	// check how long it takes for the pulse to come back to the sensor
	echoTime = pulseIn(echoPin, HIGH);
	// calculate the distance of the object that reflected the pulse
	calculatedDistance = echoTime / 148.0;

	return calculatedDistance;
}