#include "Controller.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "System.h"

Controller::Controller()
: newReadings(xSemaphoreCreateBinary())
{
}

void Controller::task(void *args)
{
	// La tarea arranca ante la primera lectura
	// Las listas están inicialmente vacias, asi que esto si o si pasa.
	xSemaphoreTake(newReadings, portMAX_DELAY);
	while (true) {
		// Se busca un semáforo prendido dentro de los activos.
		// Si se lo encuentra, nos quedamos con ese.
		// En caso contrario lo buscamos en los inactivos para apagarlo.
		bool activeFound = false;
		for (uint8_t i = 0; i < active.size() && !activeFound; i++, active.next())
			activeFound = active.current()->ledState() == LED::State::Green;

		if (!activeFound) {
			// Apagamos el que esté en verde y no deba estarlo
			for (uint8_t i = 0; i < inactive.size(); i++, inactive.next())
				if (inactive.current()->ledState() == LED::State::Green)
					inactive.current()->halt();

			// Prendemos el primer activo
			if (active.size() != 0)
				active.next()->go();
		}

		while (xSemaphoreTake(newReadings, System::TURN_DURATION / portTICK_PERIOD_MS) == pdFALSE)
		{
			// No hubo un cambio de estado, sólo tenemos que ir cambiando de semáforo
			if (active.size() != 0) {
				active.next()->halt();
				active.current()->go();
			}
		}

	}
}

void Controller::receive(Array<Sensor, System::MAX_LAMPS> &sensors)
{
	CircularList<Lamp, System::MAX_LAMPS> newActive, newInactive;

	// Armamos las listas a partir de los datos de los sensores
	for (uint8_t i = 0; i < sensors.size(); i++) {
		const auto &sensor = sensors[i];
		if (sensor.value())
			newActive.add(&sensor.lamp());
		else
			newInactive.add(&sensor.lamp());
	}

	// Si cambiaron, las actualizamos y notificamos
	// TODO: concurrencia!
	if (newActive != active || newInactive != inactive) {
		active = newActive;
		inactive = newInactive;
		xSemaphoreGive(newReadings);
	}
}
