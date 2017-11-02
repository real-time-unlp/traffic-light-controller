#include <TrafficLight.h>
#include <PedestrianLight.h>
#include <Arduino_FreeRTOS.h>

PedestrianLight::PedestrianLight(LED &&led, Controller &controller, uint8_t sensorPin, uint8_t greenDuration)
: TrafficLight(led, controller, sensorPin, greenDuration),
  mMutex(xSemaphoreCreateMutex())
{

}

void PedestrianLight::taskFunction(void *args)
{

}

void PedestrianLight::sensingTaskFunction(void *args)
{

}
