#ifndef LAMP_H
#define LAMP_H

#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "LED.h"
#include <stdint.h>

class Lamp
{
	private:
		const uint8_t mId;
		const volatile SemaphoreHandle_t run_sem;
		const volatile SemaphoreHandle_t halt_sem;
		LED led;

	public:
		Lamp(LED &led, uint8_t id);
		void task(void *args);
		void go();
		void halt();
		LED::State ledState();
		uint8_t id();
};

#endif
