#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "circular_list.h"

class Controller
{
private:
	CircularList<Lamp, 4> active, inactive;
	const volatile SemaphoreHandle_t new_readings;
	void wait_for_readings();

public:
	Controller();
	void task(void *args);
	void receive_new_readings(const circular_list actives, const circular_list disabled);
};

#endif