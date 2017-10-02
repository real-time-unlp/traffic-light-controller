#include <Controller.h>
#include <semphr.h>
#include <System.h>

Controller::Controller()
: full(xSemaphoreCreateCounting(1, 0)),
  empty(xSemaphoreCreateCounting(1, 1))
{
}

void Controller::task(void *args)
{
	// La tarea arranca ante la primera lectura
	// Las listas están inicialmente vacias, asi que esto si o si pasa.
	xSemaphoreTake(full, portMAX_DELAY);
	active = this->newActive;
	inactive = this->newInactive;
	xSemaphoreGive(empty);
	while (true) {
		// Se busca un semáforo prendido dentro de los activos.
		// Si se lo encuentra, nos quedamos con ese.
		// En caso contrario lo buscamos en los inactivos para apagarlo.
		bool activeFound = false;
		for (uint8_t i = 0; i < active.size() && !activeFound; i++)
			if (active.next()->ledState() == LED::State::Green) {
				activeFound = true;
				active.prev();
			}

		if (!activeFound) {
			// Apagamos el que esté en verde y no deba estarlo
			bool inactiveFound = false;
			for (uint8_t i = 0; i < inactive.size() && !inactiveFound; i++, inactive.next())
				if (inactive.current()->ledState() == LED::State::Green) {
					inactive.current()->halt();
					//delay(System::TRANSITION_TO_ANOTHER_LAMP);
					inactiveFound = true;
				}

			// Prendemos el primer activo
			if (active.size() != 0)
				active.current()->go();
		}


		while (xSemaphoreTake(full, System::TURN_DURATION / portTICK_PERIOD_MS) == pdFALSE) {
			// No hubo un cambio de estado, sólo tenemos que ir cambiando de semáforo
			// Solo alternar semáforos y hay mas de uno participando
			if (active.size() > 1) {
				active.next()->halt();
				delay(System::TRANSITION_TO_ANOTHER_LAMP);
				if (!uxSemaphoreGetCount(full))
					active.current()->go();
			}
		}
		
		active = this->newActive;
		inactive = this->newInactive;
		xSemaphoreGive(empty);
	}
}

void Controller::receive(Array<Sensor, System::MAX_LAMPS> &sensors)
{
	volatile CircularList<Lamp, System::MAX_LAMPS> newActive, newInactive;
	// Armamos las listas a partir de los datos de los sensores
	for (uint8_t i = 0; i < sensors.size(); i++) {
		const auto &sensor = sensors[i];
		if (sensor.value())
			newActive.add(&sensor.lamp());
		else
			newInactive.add(&sensor.lamp());
	}

	// Si cambiaron, las actualizamos y notificamos
	if (this->newActive != newActive || this->newInactive != newInactive) {
		xSemaphoreTake(empty, portMAX_DELAY);
		this->newActive = newActive;
		this->newInactive = newInactive;
		xSemaphoreGive(full);
	}
}
