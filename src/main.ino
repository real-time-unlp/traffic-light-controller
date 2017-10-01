#include <Arduino_FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <LED.h>
#include <Lamp.h>
#include <Controller.h>
#include <SensorMonitor.h>
#include <System.h>
#include <Array.h>
#include <Sensor.h>

Array<LED, System::MAX_LAMPS> leds ({
	LED(11, 10, 9),
	LED(8, 7, 6)
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
		xTaskCreate(lampTask, "Lamp " + i, configMINIMAL_STACK_SIZE, (void*) (&taskIndices[i]), System::LAMP_PRIORITY, NULL);
	
	xTaskCreate(controllerTask, "Controller", configMINIMAL_STACK_SIZE, NULL, System::CONTROLLER_PRIORITY, NULL);
	xTaskCreate(sensorMonitorTask, "Sensor Monitor", configMINIMAL_STACK_SIZE, NULL, System::SENSOR_MONITOR_PRIORITY, NULL);

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

