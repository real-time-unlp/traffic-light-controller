#include <Arduino_FreeRTOS.h>
#include "LED.h"
#include "Lamp.h"
#include "Controller.h"
#include "SensorMonitor.h"
#include "System.h"
#include "Array.h"
#include "Sensor.h"

/*
LED leds[System::MAX_LAMPS] = { LED(0,1,2), LED(3,4,5), LED(6,7,8), LED(9,10,11) };
Lamp lamps[System::MAX_LAMPS] = { Lamp(leds[0], 0), Lamp(leds[1], 1), Lamp(leds[2], 2), Lamp(leds[3], 3) };
Sensor sensors[System::MAX_LAMPS] = { Sensor(lamps[0], 0, HIGH), Sensor(lamps[1], 1, HIGH), Sensor(lamps[2], 2, HIGH), Sensor(lamps[3], 3, HIGH) };*/
Array<LED, System::MAX_LAMPS> leds;
Array<Lamp, System::MAX_LAMPS> lamps;
Array<Sensor, System::MAX_LAMPS> sensors;
Controller controller;
SensorMonitor sensorMonitor(controller, sensors);

void lampTask(void *args);
void controllerTask(void *args);
void sensorMonitorTask(void *args);

void setup()
{
	Serial.begin(9600);
	Serial.println("Inicio de Control de Tráfico");
	
	for(uint8_t i = 0; i < System::MAX_LAMPS; i++) {
		uint8_t index = i * 3;
		leds[i]((uint8_t) index, (uint8_t) (index + 1), (uint8_t) (index + 2));
		lamps[i](leds[i], i);
		sensors[i](lamps[i], i, true);
		xTaskCreate(lampTask, "Lamp " + i, 128, (void *) i, System::LAMP_PRIORITY, NULL); //TODO creo que no está bien pasar "i" porque despues cambia de valor.
	}
	
	xTaskCreate(controllerTask, "Controller", 128, NULL, System::CONTROLLER_PRIORITY, NULL);
	xTaskCreate(sensorMonitorTask, "Sensor Monitor", 128, NULL, System::SENSOR_MONITOR_PRIORITY, NULL);

	vTaskStartScheduler();
}

void loop()
{
}

void lampTask(void *args)
{
	uint8_t lampIndex = (int) args;
	Serial.println("Inicio de tarea Lamp " + lampIndex);
	lamps[lampIndex].task(args);
}

void controllerTask(void *args)
{
	Serial.println("Inicio de tarea Controller");
	controller.task(args);
}

void sensorMonitorTask(void *args)
{
	Serial.println("Inicio de tarea Sensor Monitor");
	sensorMonitor.task(args);
}

