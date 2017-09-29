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
	// TODO: serializar acceso a estas dos
	CircularList<Lamp, System::MAX_LAMPS> active, inactive;
	const volatile SemaphoreHandle_t newReadings;
	const volatile SemaphoreHandle_t listsMutex;

public:
	Controller();
	void task(void *args);
	void receive(Array<Sensor, System::MAX_LAMPS> &sensors);
};

#endif
