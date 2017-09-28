#include "Controller.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

void Controller::task(void *args)
{
	while (true) {
		xSemaphoreTake(newReadings, portMAX_DELAY);
		// Se busca un semáforo prendido dentro de los activos.
		// Si se lo encuentra, nos quedamos con ese.
		// En caso contrario lo buscamos en los inactivos para apagarlo.
		bool activeFound = false;
		for (uint8_t i = 0; i < active.size() && !activeFound; i++)
			activeFound = active.next()->ledState() == LED::State::Green;

		if (activeFound) {
			// Nos posicionamos en el que ya estaba en verde
			active.prev();
		} else {
			// Apagamos el que este en verde y no deba estarlo
			for (uint8_t i = 0; i < inactive.size(); i++) {
				if (inactive.current()->ledState() == LED::State::Green)
					inactive.current()->halt();
				inactive.next();
			}
		}
	}
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
