#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "CircularList.h"
#include "System.h"
#include "Lamp.h"
#include "Sensor.h"
#include "Array.h"

class Controller {
private:
	volatile CircularList<Lamp, System::MAX_LAMPS> active, inactive,
					newActive, newInactive;
	const volatile SemaphoreHandle_t full;
	const volatile SemaphoreHandle_t empty;

public:
	Controller();
	void task(void *args);
	void receive(Array<Sensor, System::MAX_LAMPS> &sensors);
};

#endif
