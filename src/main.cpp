#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <TrafficLight.h>
#include <PedestrianLight.h>
#include <semphr.h>

TrafficLight traffics[TrafficLight::AMOUNT - 1] = {
	TrafficLight(LED(2, 1, 0), A0, 0, TrafficLight::GreenAvenueDuration),
	TrafficLight(LED(5, 4, 3), A1, 1, TrafficLight::GreenAvenueDuration),
	TrafficLight(LED(8, 7, 6), A2, 2, TrafficLight::GreenAvenueDuration),
	TrafficLight(LED(11, 10, 9), A3, 3, TrafficLight::GreenAvenueDuration)
};

PedestrianLight walker(LED(13, 12, 12), A4, 4, TrafficLight::GreenAvenueDuration);

void setup()
{
	for(int i = 0; i < TrafficLight::AMOUNT - 1; i++)
		TrafficLight::lights[i] = traffics + i;
	TrafficLight::lights[TrafficLight::AMOUNT - 1] = &walker;

	xSemaphoreGive(traffics[0].mutex());

	vTaskStartScheduler();
}


void loop()
{
}
