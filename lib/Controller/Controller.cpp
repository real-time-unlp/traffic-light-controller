#include <Controller.h>
#include <Arduino.h>
#include <LED.h>

Controller::Controller()
:
	mSemaphore(xSemaphoreCreateCounting(1, 1)),
	mTrafficLights{
		TrafficLight(LED(2, 1, 0), *this, A0, mSemaphore, TrafficLight::GreenAvenueDuration),
		TrafficLight(LED(5, 4, 3), *this, A1, mSemaphore, TrafficLight::GreenAvenueDuration),
		TrafficLight(LED(8, 7, 6), *this, A2, mSemaphore, TrafficLight::GreenAvenueDuration)
		//TrafficLight(LED(11, 10, 9), *this, A3, mSemaphore, TrafficLight::GreenAvenueDuration)
	}
	//mPedestrianLight(LED(13, 13, 12), *this, A4, mSemaphore, TrafficLight::GreenAvenueDuration)
{
	senseAll();
}

void Controller::senseAll()
{
	for (uint8_t i = 0; i < TRAFFIC_LIGHTS; i++)
		mTrafficLights[i].sense();
	//mPedestrianLight.sense();
}

bool Controller::isOnlyOneActive(const TrafficLight &light) const
{
	uint8_t activeCount = 0;
	for (uint8_t i = 0; i < TRAFFIC_LIGHTS; i++)
		if (mTrafficLights[i].active())
			activeCount++;

	//if (mPedestrianLight.active())
	//	activeCount++;

	return activeCount == 1 && light.active();
}
