
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

void setup() {
	// 115200 is for VS Code
	// Serial.begin(115200);
	// change to 9600 if using Arduino IDE
	Serial.begin(9600);
}

void loop() {
	moveForward();
}

void moveForward() {
	rightMotor(1000);
	leftMotor(1000);
}

void moveBackward() {
	rightMotor(-255);
	leftMotor(-255);
}

void turnLeft() {
	rightMotor(-255);
	leftMotor(255);
}

void turnRight() {
	rightMotor(255);
	leftMotor(-255);
}

void stop() {
	rightMotor(0);
	leftMotor(0);
	delay(400);
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