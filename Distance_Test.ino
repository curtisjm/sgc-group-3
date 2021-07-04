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
	// rightDistance = getDistance();

}