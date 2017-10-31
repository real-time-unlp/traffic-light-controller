#pragma once
#include <stdint.h>

class LED {
public:
	LED(uint8_t redPin, uint8_t yellowPin, uint8_t bluePin);
	void red();
	void yellow();
	void green();
	void off();
private:
	const uint8_t redPin;
	const uint8_t greenPin;
	const uint8_t bluePin;
};
