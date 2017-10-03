#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <CircularList.h>
#include <System.h>
#include <Lamp.h>
#include <Sensor.h>
#include <Array.h>

/*
 * Esta clase implementa la tarea principal del sistema. Esta tarea recibe desde
 * SensorMonitor el estado de los sensores y actualiza la estrategia de
 * planificación de los semáforos.
 * 
 * task() y receive() corren en distintas tareas. task() corre continuamente, se
 * duerme sobre los semáforos full y empty. full y empty arman una cola productor
 * consumidor de manera que esta clase es el consumidor y SensorMonitor es el 
 * productor.
 * 
 * Cuando se ejecuta receive() desde otra tarea (específicamente desde la de 
 * SensorMonitor), se arman los conjuntos de luces activas e inactivas y se las
 * deja para que task() eventualmente las consuma. Esto se hace solo si se detecta
 * una diferencia en los conjuntos viejos y los nuevos.
 */
class Controller {
private:
	// Con estas variables trabaja task()
	volatile CircularList<Lamp, System::MAX_LAMPS> active, inactive;
	// Estas variables forman el buffer del productor-consumidor
	// Cuando task() consume del buffer, copia estas hacia active e inactive
	volatile CircularList<Lamp, System::MAX_LAMPS> newActive, newInactive;
	const volatile SemaphoreHandle_t full, empty;

	bool findActiveOn();
	void turnOffPrevious();
	void transition();
public:
	Controller();
	void task(void *args);
	void receive(Array<Sensor, System::MAX_LAMPS> &sensors);
};

#endif
