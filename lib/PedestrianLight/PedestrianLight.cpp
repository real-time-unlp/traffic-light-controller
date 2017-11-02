#include <PedestrianLight.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

PedestrianLight::PedestrianLight(LED &&led, Controller &controller, uint8_t sensorPin, uint8_t greenDuration)
: TrafficLight(static_cast<LED&&>(led), controller, sensorPin, greenDuration),
  mMutex(xSemaphoreCreateCounting(1, 1))
{

}

void PedestrianLight::taskFunction(void *args)
{

}

void PedestrianLight::sensingTaskFunction(void *args)
{

}
