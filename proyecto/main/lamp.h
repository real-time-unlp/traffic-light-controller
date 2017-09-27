#ifndef LAMP_H
#define LAMP_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "led.h"
#include "config.h"

class Lamp
{
	private:
		const unsigned char id;
		const volatile SemaphoreHandle_t run_sem;
		const volatile SemaphoreHandle_t halt_sem;
		const Led* led;

	public:
		Lamp(const Led* led, const unsigned char id);
		void task(void *args);
		void run();
		void halt();
		unsigned char get_status();
		unsigned char get_id();
		~Lamp();
};

#endif
