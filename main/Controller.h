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
	CircularList<Lamp, System::MAX_LAMPS> active, inactive;
	const volatile SemaphoreHandle_t newReadings;

public:
	Controller();
	void task(void *args);
	void receive(const Array<Sensor, System::MAX_LAMPS> &sensors);
};

#endif
