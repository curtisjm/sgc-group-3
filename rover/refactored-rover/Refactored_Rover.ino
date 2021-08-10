// code for rover

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

// how long to wait before getting new distance in a turn
const int TURN_DELAY = 400;
const int STOP_TIME = 1000;

// keep track of how long the rover turns so it can get back on a straight track
float turnTime = 0;
// used to keep track of last recorded time in turn loop
float lastTime = 0;
// how long it takes to pass the obstacle
float forwardTime = 0;

// initialize distance tracking variables
float frontDistance = 0;
float rightDistance = 0;
float leftDistance = 0;
// variable used to keep track of distance as the rover is rotating
float newDistance = 0;

// remember which direction the rover turned so we can go back the opposite dierection
bool didTurnLeft = true;

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
	
	Serial.println("Setup complete.");
}

void loop() {
	Serial.println("Start of loop...");

	// assign distances from front sensor to its variable
	frontDistance = getDistance(trigPinFront, echoPinFront);
	Serial.println("Front: " + String(frontDistance));

	// once distance is less than our chosen threshold
	if(frontDistance < 20) {
		stop(STOP_TIME);
		// check distances on either side of rover to see which direction has more room to travel towards
		rightDistance = getDistance(trigPinRight, echoPinRight);
		leftDistance = getDistance(trigPinLeft, echoPinLeft);

		// output side distances to serial monitor
		Serial.println("R: " + String(rightDistance) + "	L: " + String(leftDistance));
		
		didTurnLeft = (rightDistance < leftDistance) ? true : false;

		rotateRover();
		// passObstacle();
		// moveBackOnLine();
	}

	moveForward(400);
}

void rotateRover() {
	Serial.println("Rotating rover...");
	// variable used to keep track of distance as the rover is rotating
	newDistance = getDistance(trigPinFront, echoPinFront);
	Serial.println("New: " + String(newDistance));
	// keep track of how long the rover turns so it can get back on a straight track
	turnTime = 0;
	// get initial time reading
	lastTime = millis();

	// turn car until there is a free path ahead
	while((newDistance - frontDistance) < 20) {
		Serial.println("In turn loop...");
		Serial.println("Original:" + String(frontDistance) + "	New:" + String(newDistance));
		didTurnLeft ? turnLeft(TURN_DELAY) : turnRight(TURN_DELAY);
		newDistance = getDistance(trigPinFront, echoPinFront);
		// keep track of how long we are in the turn loop by adding the time change onto turnTime
		turnTime += (millis() - lastTime);
		lastTime = millis();
	}
	didTurnLeft ? turnLeft(TURN_DELAY) : turnRight(TURN_DELAY);
	stop(STOP_TIME);
}

void passObstacle() {
	forwardTime = 0;
	lastTime = millis();
	while(leftDistance < 10 && rightDistance < 10) {
		moveForward(0);
		rightDistance = getDistance(trigPinRight, echoPinRight);
		leftDistance = getDistance(trigPinLeft, echoPinLeft);
		forwardTime += (millis() - lastTime);
		lastTime = millis();
	}
	stop(STOP_TIME);
}

void moveBackOnLine() {
	// turn car back toward original line
	didTurnLeft ? turnRight(turnTime * 2) : turnLeft(turnTime * 2);
	// travel same distance forward as before to get back on line
	moveForward(forwardTime);
	stop(STOP_TIME);
	// turn back forward
	didTurnLeft ? turnLeft(turnTime) : turnRight(turnTime);
	stop(STOP_TIME);
}

void moveForward(float delayTime) {
	rightMotor(255);
	leftMotor(255);
	delay(delayTime);
}

void moveBackward(float delayTime) {
	rightMotor(-255);
	leftMotor(-255);
	delay(delayTime);
}

void turnLeft(float delayTime) {
	rightMotor(-170);
	leftMotor(170);
	delay(delayTime);
}

void turnRight(float delayTime) {
	rightMotor(170);
	leftMotor(-170);
	delay(delayTime);
}

void stop(float delayTime) {
	rightMotor(0);
	leftMotor(0);
	delay(delayTime);
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