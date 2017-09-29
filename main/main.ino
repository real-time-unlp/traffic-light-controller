#include <Arduino_FreeRTOS.h>
#include "LED.h"
#include "Lamp.h"
#include "Controller.h"
#include "SensorMonitor.h"
#include "System.h"
#include "Array.h"
#include "Sensor.h"

Array<LED, System::MAX_LAMPS> leds ({
	LED(0,1,2),
	LED(3,4,5),
	LED(6,7,8),
	LED(9,10,11)
});

Array<Lamp, System::MAX_LAMPS> lamps ({
	Lamp(leds[0], 0),
	Lamp(leds[1], 1),
	Lamp(leds[2], 2),
	Lamp(leds[3], 3)
});

Array<Sensor, System::MAX_LAMPS> sensors ({
	Sensor(lamps[0], 0, false),
	Sensor(lamps[1], 1, false),
	Sensor(lamps[2], 2, false),
	Sensor(lamps[3], 3, false)
});

Controller controller;
SensorMonitor sensorMonitor(controller, sensors);

void lampTask(void *args);
void controllerTask(void *args);
void sensorMonitorTask(void *args);

const uint8_t taskIndices[4] {0, 1, 2, 3};

void setup()
{
	Serial.begin(9600);
	Serial.println("Inicio de Control de Tráfico");
	
	for(uint8_t i = 0; i < System::MAX_LAMPS; i++)
		xTaskCreate(lampTask, "Lamp " + i, 128, (void*) (&taskIndices + 1), System::LAMP_PRIORITY, NULL);
	
	xTaskCreate(controllerTask, "Controller", 128, NULL, System::CONTROLLER_PRIORITY, NULL);
	xTaskCreate(sensorMonitorTask, "Sensor Monitor", 128, NULL, System::SENSOR_MONITOR_PRIORITY, NULL);

	vTaskStartScheduler();
}

void loop()
{
}

void lampTask(void *args)
{
	uint8_t lampIndex = *((const uint8_t*) args);
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

