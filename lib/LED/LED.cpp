#include <LED.h>
#include <Arduino.h>

LED::LED(uint8_t redPin, uint8_t yellowPin, uint8_t greenPin)
: mRedPin(redPin),
  mYellowPin(yellowPin),
  mGreenPin(greenPin)
{
	pinMode(mRedPin, OUTPUT);
	pinMode(mYellowPin, OUTPUT);
	pinMode(mGreenPin, OUTPUT);
	off();
}

void LED::red()
{
	digitalWrite(mYellowPin, LOW);
	digitalWrite(mGreenPin, LOW);
	digitalWrite(mRedPin, HIGH);
}

void LED::yellow()
{
	digitalWrite(mRedPin, LOW);
	digitalWrite(mGreenPin, LOW);
	digitalWrite(mYellowPin, HIGH);
}

void LED::green()
{
	digitalWrite(mRedPin, LOW);
	digitalWrite(mYellowPin, LOW);
	digitalWrite(mGreenPin, HIGH);
}

void LED::off()
{
	digitalWrite(mRedPin, LOW);
	digitalWrite(mYellowPin, LOW);
	digitalWrite(mGreenPin, LOW);
}
