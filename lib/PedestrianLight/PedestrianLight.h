#pragma once
#include <stdint.h>
#include <Arduino_FreeRTOS.h>
#include <TrafficLight.h>

class Controller;

class PedestrianLight : public TrafficLight {
public:
	PedestrianLight(Controller &controller, uint8_t bitIndex, uint8_t sensorPin, uint8_t greenDuration);
private:
	void taskFunction(void *args);
};
