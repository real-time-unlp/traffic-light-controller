#ifndef LAMP_H
#define LAMP_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <LED.h>
#include <stdint.h>

/*
 * Esta clase maneja el color actual del semáforo correspondiente a un tramo.
 * Tiene funciones que "bloquean".
 */
class Lamp {
private:
	const uint8_t mId;
	const volatile SemaphoreHandle_t run_sem, halt_sem;
	LED &led;

public:
	Lamp(LED &led, uint8_t id);

	void task(void *args);

	// Pone este semáforo en verde si es que está en rojo
	void go();

	// Pone este semáforo en rojo, pasando por el amarillo, si es que está verde
	void halt();

	LED::State ledState() const;
	uint8_t id() const;
};

#endif
