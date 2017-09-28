#ifndef LED_H
#define LED_H

#include <Arduino.h>
#include <stdint.h>

class LED
{
	private:
		const uint8_t redPin;
		const uint8_t yellowPin;
		const uint8_t greenPin;

	public:
		enum class State {Red, Yellow, Green, Off};
		State mState;
		LED(uint8_t greenPin, uint8_t yellowPin, uint8_t redPin);
		void set(State newState);
		State state();
};

#endif
