#include "LED.h"
#include <Arduino.h>

LED::LED(uint8_t greenPin, uint8_t yellowPin, uint8_t redPin)
: greenPin(greenPin),
  yellowPin(yellowPin),
  redPin(redPin)
{
	set(State::Off);
}

void LED::set(State newState)
{
	mState = newState;
	switch (mState) {
	case State::Red:
		digitalWrite(greenPin, LOW);
		digitalWrite(yellowPin, LOW);
		digitalWrite(redPin, HIGH);
		break;
	case State::Yellow:
		digitalWrite(greenPin, LOW);
		digitalWrite(yellowPin, HIGH);
		digitalWrite(redPin, LOW);
		break;
	case State::Green:
		digitalWrite(greenPin, HIGH);
		digitalWrite(yellowPin, LOW);
		digitalWrite(redPin, LOW);
		break;
	case State::Off:
		digitalWrite(greenPin, LOW);
		digitalWrite(yellowPin, LOW);
		digitalWrite(redPin, LOW);
		break;
	}
}

LED::State LED::state()
{
	return mState;
}