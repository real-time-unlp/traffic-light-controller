#include "Lamp.h"
#include "System.h"
#include <Arduino.h>

Lamp::Lamp(LED &led, uint8_t id)
: mId(id),
  run_sem(xSemaphoreCreateBinary()),
  halt_sem(xSemaphoreCreateBinary()),
  led(led)
{
	if (run_sem == NULL || halt_sem == NULL)
		Serial.println("Algun semaforo en Lamp no se ha iniciado correctamente");
}

void Lamp::task(void *args)
{
	while (1) {
		led.set(LED::State::Red);
		if (xSemaphoreTake(run_sem, portMAX_DELAY) == pdTRUE) {
			led.set(LED::State::Green);
			if (xSemaphoreTake(halt_sem, portMAX_DELAY) == pdTRUE) {
				led.set(LED::State::Yellow);
				delay(System::YELLOW_DURATION);
			} else {
				Serial.println("No se adquirio el semaforo 'halt_sem'");
			}
		} else {
			Serial.println("No se adquirio el semaforo 'run_sem'");
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
