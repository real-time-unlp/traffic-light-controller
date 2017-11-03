#pragma once
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <TrafficLight.h>
#include "../PedestrianLight/PedestrianLight.h"

class PedestrianLight;

class Controller {
public:
	static constexpr uint8_t TRAFFIC_LIGHTS = 4;

	Controller();
	bool isOnlyOneActive(const TrafficLight &light) const;
	void senseAll();
private:
	SemaphoreHandle_t mSemaphore;
	TrafficLight mTrafficLights[TRAFFIC_LIGHTS];
	PedestrianLight mPedestrianLight;
};
