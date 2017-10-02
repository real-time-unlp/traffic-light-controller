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
	LED(5, 4, 3),
	LED(8, 7, 6)
});

Array<Lamp, System::MAX_LAMPS> lamps ({
	Lamp(leds[0], 0),
	Lamp(leds[1], 1),
	Lamp(leds[2], 2)
});

Array<Sensor, System::MAX_LAMPS> sensors ({
	Sensor(lamps[0], A0, HIGH),
	Sensor(lamps[1], A1, HIGH),
	Sensor(lamps[2], A2, HIGH)
});

Controller controller;
SensorMonitor sensorMonitor(controller, sensors);

void lampTask(void *args);
void controllerTask(void *args);
void sensorMonitorTask(void *args);

void setup()
{
	for(uint8_t i = 0; i < System::MAX_LAMPS; i++)
		xTaskCreate(lampTask, "", configMINIMAL_STACK_SIZE, (void*) (&lamps[i]), System::LAMP_PRIORITY, NULL);
	
	xTaskCreate(controllerTask, "", configMINIMAL_STACK_SIZE, NULL, System::CONTROLLER_PRIORITY, NULL);
	xTaskCreate(sensorMonitorTask, "", configMINIMAL_STACK_SIZE, NULL, System::SENSOR_MONITOR_PRIORITY, NULL);

	vTaskStartScheduler();
}

void loop()
{
}

void lampTask(void *args)
{
	Lamp *lamp = (Lamp*) args;
	lamp->task(NULL);
}

void controllerTask(void *args)
{
	controller.task(args);
}

void sensorMonitorTask(void *args)
{
	sensorMonitor.task(args);
}

