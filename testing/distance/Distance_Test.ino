// testing the distance censors to check accuracy and how to interface with multiple of them

const int trigPinFront = 6;
const int echoPinFront = 5;

const int trigPinRight = 3;
const int echoPinRight = 2;

const int trigPinLeft = 7;
const int echoPinLeft = 4;

float frontDistance = 0;
float rightDistance = 0;
float leftDistance = 0;

void setup() {
	pinMode(trigPinFront, OUTPUT);
	pinMode(echoPinFront, INPUT);
	pinMode(trigPinRight, OUTPUT);
	pinMode(echoPinRight, INPUT);
	pinMode(trigPinLeft, OUTPUT);
	pinMode(echoPinLeft, INPUT);

	Serial.begin(115200);
}

void loop() {
	frontDistance = getDistance(trigPinFront, echoPinFront);
	rightDistance = getDistance(trigPinRight, echoPinRight);
	leftDistance = getDistance(trigPinLeft, echoPinLeft);

	Serial.println("Front: " + String(frontDistance));
	Serial.println("R: " + String(rightDistance) + "	L: " + String(leftDistance));

	delay(50);
}

float getDistance(const int trigPin, const int echoPin) {
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	float echoTime = pulseIn(echoPin, HIGH);
	float calculatedDistance = echoTime / 148.0;

	return calculatedDistance;
}