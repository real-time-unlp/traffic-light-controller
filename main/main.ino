#include <Arduino_FreeRTOS.h>
#include "LED.h"
#include "Lamp.h"
#include "Controller.h"
#include "SensorMonitor.h"
#include "System.h"
#include "Array.h"
#include "Sensor.h"

/*
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
	Sensor(lamps[0], A0, HIGH),
	Sensor(lamps[1], A1, HIGH),
	Sensor(lamps[2], A2, HIGH),
	Sensor(lamps[3], A3, HIGH)
});

const uint8_t taskIndices[System::MAX_LAMPS] {0, 1, 2, 3};*/

Array<LED, System::MAX_LAMPS> leds ({
	LED(2, 1, 0),
	LED(5, 4, 3)
});

Array<Lamp, System::MAX_LAMPS> lamps ({
	Lamp(leds[0], 0),
	Lamp(leds[1], 1)
});

Array<Sensor, System::MAX_LAMPS> sensors ({
	Sensor(lamps[0], A0, HIGH),
	Sensor(lamps[1], A1, HIGH)
});

const uint8_t taskIndices[System::MAX_LAMPS] { 0, 1 };

Controller controller;
SensorMonitor sensorMonitor(controller, sensors);

void lampTask(void *args);
void controllerTask(void *args);
void sensorMonitorTask(void *args);

void setup()
{
	for(uint8_t i = 0; i < System::MAX_LAMPS; i++)
		xTaskCreate(lampTask, "Lamp " + i, 128, (void*) (&taskIndices[i]), System::LAMP_PRIORITY, NULL);
	
	xTaskCreate(controllerTask, "Controller", 128, NULL, System::CONTROLLER_PRIORITY, NULL);
	xTaskCreate(sensorMonitorTask, "Sensor Monitor", 128, NULL, System::SENSOR_MONITOR_PRIORITY, NULL);

	vTaskStartScheduler();
}

void loop()
{
}

void lampTask(void *args)
{
	uint8_t lampIndex = *((const uint8_t *) args);
	lamps[lampIndex].task(args);
}

void controllerTask(void *args)
{
	controller.task(args);
}

void sensorMonitorTask(void *args)
{
	sensorMonitor.task(args);
}

