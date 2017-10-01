#ifndef LED_H
#define LED_H

#include <stdint.h>

class LED {
public:
	enum class State {Red, Yellow, Green, Off};
	LED(uint8_t redPin, uint8_t yellowPin, uint8_t greenPin);
	void set(State newState);
	State state();
	
private:
	const uint8_t redPin;
	const uint8_t yellowPin;
	const uint8_t greenPin;
	State mState;
};

#endif
