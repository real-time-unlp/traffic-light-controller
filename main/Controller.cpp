#include "Controller.h"
#include <Arduino_FreeRTOS.h>

void Controller::task(void *args)
{

}

void Controller::receive(Array<Sensor, System::MAX_LAMPS> &sensors)
{
	CircularList<Lamp, System::MAX_LAMPS> newActive, newInactive;

	for (uint8_t i = 0; i < sensors.size(); i++) {
		const auto &sensor = sensors[i];
		if (sensor.value())
			newActive.add(&sensor.lamp());
		else
			newInactive.add(&sensor.lamp());
	}

	if (newActive != active || newInactive != inactive) {
		active = newActive;
		inactive = newInactive;
		xSemaphoreGive(newReadings);
	}
}
