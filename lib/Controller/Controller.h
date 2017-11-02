#pragma once
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <TrafficLight.h>
#include "../PedestrianLight/PedestrianLight.h"

class PedestrianLight;

class Controller {
public:
	static constexpr uint8_t TRAFFIC_LIGHTS = 4; 
	static constexpr BaseType_t LightLowPriority = 1;
	static constexpr BaseType_t LightHighPriority = 2;
	static constexpr uint8_t YellowLightDuration = 3;
	static constexpr uint8_t RedLightDuration = 2;

	Controller();
	bool isOnlyOneActive(const TrafficLight &light) const;
private:
	TrafficLight mTrafficLights[TRAFFIC_LIGHTS];
	PedestrianLight mPedestrianLight;
	void senseAll();
};
