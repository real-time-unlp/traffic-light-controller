#ifndef LED_H
#define LED_H

#include <Arduino.h>

#define GREEN_STATUS    0
#define YELLOW_STATUS   1
#define RED_STATUS      2
#define OFF_STATUS      3

class Led
{
	private:
		const unsigned char green_pin;
		const unsigned char yellow_pin;
		const unsigned char red_pin;
		unsigned char led_status;

	public:
		Led(const unsigned char green_pin, const unsigned char yellow_pin, const unsigned char red_pin);
		void on();
		void off();
		void green();
		void yellow();
		void red();
		unsigned char get_status();
		~Led();
};

#endif
