#pragma once
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <TrafficLight.h>
#include "../PedestrianLight/PedestrianLight.h"

class PedestrianLight;

class Controller {
public:
	static constexpr uint8_t TRAFFIC_LIGHTS = 3;

	static constexpr BaseType_t LightHighPriority = 3;
	static constexpr BaseType_t LightLowPriority = 2;
	static constexpr BaseType_t SensingTaskPriority = 1;

	static constexpr uint16_t GreenAvenueDuration = 1000;
	static constexpr uint16_t YellowLightDuration = 500;
	static constexpr uint16_t RedLightDuration = 500;

	Controller();
	bool isOnlyOneActive(const TrafficLight &light) const;
	void senseAll();
private:
	SemaphoreHandle_t mSemaphore;
	TrafficLight mTrafficLights[TRAFFIC_LIGHTS];
	//PedestrianLight mPedestrianLight;
};
