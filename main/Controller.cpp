#include "Controller.h"
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "System.h"

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
	Serial.println("=======================");
	Serial.println("Globales");
	Serial.print("Active size = ");
	Serial.println(this->newActive.size());
	Serial.print("Inactive size = ");
	Serial.println(this->newInactive.size());
	active = this->newActive;
	inactive = this->newInactive;
	Serial.println("=======================");
	Serial.println("Globales");
	Serial.print("Active size = ");
	Serial.println(this->active.size());
	Serial.print("Inactive size = ");
	Serial.println(this->inactive.size());
	xSemaphoreGive(empty);
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
				active.current()->go();
		}


		while (xSemaphoreTake(full, System::TURN_DURATION / portTICK_PERIOD_MS) == pdFALSE) {
			// No hubo un cambio de estado, sólo tenemos que ir cambiando de semáforo
			// Solo alternar semáforos y hay mas de uno participando
			if (active.size() > 1) {
				active.next()->halt();
				active.current()->go();
			}
		}

		Serial.println("=======================");
		Serial.println("Globales");
		Serial.print("Active size = ");
		Serial.println(this->newActive.size());
		Serial.print("Inactive size = ");
		Serial.println(this->newInactive.size());
		active = this->newActive;
		inactive = this->newInactive;
		Serial.println("=======================");
		Serial.println("Globales");
		Serial.print("Active size = ");
		Serial.println(this->active.size());
		Serial.print("Inactive size = ");
		Serial.println(this->inactive.size());
		xSemaphoreGive(empty);
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
	if (this->newActive != newActive || this->newInactive != newInactive) {
		xSemaphoreTake(empty, portMAX_DELAY);
		Serial.println("=======================");
		Serial.println("Locales");
		Serial.print("Active size = ");
		Serial.println(newActive.size());
		Serial.print("Inactive size = ");
		Serial.println(newInactive.size());
		this->newActive = newActive;
		this->newInactive = newInactive;
		Serial.println("=======================");
		Serial.println("Globales");
		Serial.print("Active size = ");
		Serial.println(this->newActive.size());
		Serial.print("Inactive size = ");
		Serial.println(this->newInactive.size());
		xSemaphoreGive(full);
	}
}
