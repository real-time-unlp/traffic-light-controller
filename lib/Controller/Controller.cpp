#include <Controller.h>
#include <Arduino.h>
#include <LED.h>

Controller::Controller()
:
	mSemaphore(xSemaphoreCreateCounting(1, 1)),
	mTrafficLights{
		TrafficLight(LED(0, 0, 0), *this, 0, mSemaphore, 30),
		TrafficLight(LED(0, 0, 0), *this, 0, mSemaphore, 30),
		TrafficLight(LED(0, 0, 0), *this, 0, mSemaphore, 30),
		TrafficLight(LED(0, 0, 0), *this, 0, mSemaphore, 30)
	},
	mPedestrianLight(LED(0, 0, 0), *this, 0, mSemaphore, 30)
{
	senseAll();
	vTaskPrioritySet(mPedestrianLight.task(), LightHighPriority);
}

void Controller::senseAll()
{
	for (uint8_t i = 0; i < TRAFFIC_LIGHTS; i++)
		mTrafficLights[i].sense();
	mPedestrianLight.sense();
}

bool Controller::isOnlyOneActive(const TrafficLight &light) const
{
	uint8_t activeCount = 0;
	for (uint8_t i = 0; i < TRAFFIC_LIGHTS; i++)
		if (mTrafficLights[i].active())
			activeCount++;

	if (mPedestrianLight.active())
		activeCount++;

	return activeCount == 1 && light.active();
}
