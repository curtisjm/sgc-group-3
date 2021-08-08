// test how to keep track of time while the rover is turning

float time = 0;
float loopTime = 0;
int x = 10000;

void setup() {
	Serial.begin(115200);
}

void loop() {
	time = millis();
	Serial.println("here");

	while(x > 0) {

		Serial.println("LT: " + String(loopTime));
		x--;
		loopTime += (millis() - time);
		time = millis();
	}
}