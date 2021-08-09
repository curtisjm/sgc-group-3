
// right motor controlled by motor A pins on driver
// control pin 1 on the motor driver for the right motor
const int AIN1 = 13;
// control pin 2 on the motor driver for the right motor
const int AIN2 = 12;
// speed control pin on the motor driver for the right motor
const int PWMA = 11;
 
// left motor controlled by motor B pins on driver
// control pin 1 on the motor driver for the left motor
const int BIN1 = 10;
// control pin 2 on the motor driver for the left motor
const int BIN2 = 9;
// speed control pin on the motor driver for the left motor
const int PWMB = 8;

// front distance sensor
const int trigPinFront = 6;
const int echoPinFront = 5;

// right distance sensor
const int trigPinRight = 3;
const int echoPinRight = 2;

// left distance censor
const int trigPinLeft = 7;
const int echoPinLeft = 4;

// initialize distance tracking variables
float frontDistance = 0;
float rightDistance = 0;
float leftDistance = 0;

void setup() {
	// trig pin outputs pulses of electricity
	// echo pin measures duration of pulses coming back
	pinMode(trigPinFront, OUTPUT);
	pinMode(echoPinFront, INPUT);
	pinMode(trigPinRight, OUTPUT);
	pinMode(echoPinRight, INPUT);
	pinMode(trigPinLeft, OUTPUT);
	pinMode(echoPinLeft, INPUT);

	// 115200 is for VS Code
	Serial.begin(115200);
	// change to 9600 if using Arduino IDE
	// Serial.begin(9600);
	moveForward();
	
	Serial.println("Setup complete.");
}

void loop() {
	frontDistance = getDistance(trigPinFront, echoPinFront);
	Serial.println(String(frontDistance));

	if(frontDistance > 20) {
		moveForward();
		// moveBackward();
	} else {
		stop();
	}
}

void moveForward() {
	rightMotor(255);
	leftMotor(255);
}

void moveBackward() {
	rightMotor(-255);
	leftMotor(-255);
}

void stop() {
	rightMotor(0);
	leftMotor(0);
	delay(400);
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

// function for driving the right motor
void rightMotor(int motorSpeed) {
	// for moving forward
	if(motorSpeed > 0) {
		digitalWrite(AIN1, HIGH);
		digitalWrite(AIN2, LOW);
	}
	// for moving backward
	else if(motorSpeed < 0) {
		digitalWrite(AIN1, LOW);
		digitalWrite(AIN2, HIGH);
	}
	// for stopping the motor
	else {
		digitalWrite(AIN1, LOW);
		digitalWrite(AIN2, LOW);
	}
	// drive motor in the previously determined direction at the given speed
	analogWrite(PWMA, abs(motorSpeed));
}

// function for driving the left motor
void leftMotor(int motorSpeed) {
	// for moving forward
	if(motorSpeed > 0) {
		digitalWrite(BIN1, HIGH);
		digitalWrite(BIN2, LOW);
	}
	// for moving backward
	else if(motorSpeed < 0) {
		digitalWrite(BIN1, LOW);
		digitalWrite(BIN2, HIGH);
	}
	// for stopping the motor
	else {
		digitalWrite(BIN1, LOW);
		digitalWrite(BIN2, LOW);
	}
	// drive motor in the previously determined direction at the given speed
	analogWrite(PWMB, abs(motorSpeed));
}