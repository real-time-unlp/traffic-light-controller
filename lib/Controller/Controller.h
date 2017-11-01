#pragma once
#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include <TrafficLight.h>
#include <../PedestrianLight/PedestrianLight.h>

class Controller {
public:
	static constexpr uint8_t TRAFFIC_LIGHTS = 4; 
	static constexpr BaseType_t LightLowPriority = 1;
	static constexpr BaseType_t LightHighPriority = 2;
	static constexpr uint8_t YellowLightDuration = 3;
	static constexpr uint8_t RedLightDuration = 2;

	Controller();
	uint8_t pollSensors() const;
	uint8_t waitForButton();
	void updatePriorities(uint8_t sensorData);
	bool isOnlyOneActive(uint8_t sensorData, uint8_t index) const;
private:
	SemaphoreHandle_t mMutex;
	TrafficLight mTrafficLights[TRAFFIC_LIGHTS];
	PedestrianLight mPedestrianLight;
};
