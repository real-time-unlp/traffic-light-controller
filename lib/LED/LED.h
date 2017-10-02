#ifndef LED_H
#define LED_H

#include <stdint.h>

/*
 * Esta clase solamente abstrae un conjunto de tres LEDs:
 * uno rojo, otro amarillo y otro azul.
 * Debería ser autoexplicativa
 */
class LED {
public:
	enum class State {Red, Yellow, Green, Off};
	LED(uint8_t redPin, uint8_t yellowPin, uint8_t greenPin);
	void set(State newState);
	State state() const;
	
private:
	const uint8_t redPin;
	const uint8_t yellowPin;
	const uint8_t greenPin;
	State mState;
};

#endif
