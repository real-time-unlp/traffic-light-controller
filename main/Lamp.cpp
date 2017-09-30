#include "Lamp.h"
#include "System.h"
#include <Arduino.h>

Lamp::Lamp(LED &led, uint8_t id)
: mId(id),
  run_sem(xSemaphoreCreateBinary()),
  halt_sem(xSemaphoreCreateBinary()),
  led(led)
{
}

void Lamp::task(void *args)
{
	while (1) {
		led.set(LED::State::Red);
		Serial.println("Hola?");
		if (xSemaphoreTake(run_sem, portMAX_DELAY) == pdTRUE) {
			led.set(LED::State::Green);
			if (xSemaphoreTake(halt_sem, portMAX_DELAY) == pdTRUE) {
				led.set(LED::State::Yellow);
				delay(System::YELLOW_DURATION);
			} else {
			}
		} else {
		}
	}
}

void Lamp::go()
{
	xSemaphoreGive(run_sem);
}

void Lamp::halt()
{
	xSemaphoreGive(halt_sem);
}

LED::State Lamp::ledState()
{
	return led.state();
}

uint8_t Lamp::id()
{
	return mId;
}
