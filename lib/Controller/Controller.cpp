#include <Controller.h>
#include <Arduino.h>

Controller::Controller()
:	mMutex(xSemaphoreCreateMutex()),
	mPedestrianLight(*this, 0, 1, 30),
	mTrafficLights{
		TrafficLight(*this, 1, 1, 30),
		TrafficLight(*this, 2, 1, 30),
		TrafficLight(*this, 3, 1, 30),
		TrafficLight(*this, 4, 1, 30)
	}
{
	for (uint8_t i = 0; i < TRAFFIC_LIGHTS; i++)
		pinMode(mTrafficLights[i].pin(), INPUT);

	pinMode(mPedestrianLight.pin(), INPUT);
	updatePriorities(0);
	vTaskPrioritySet(mPedestrianLight.task(), LightHighPriority);
}

uint8_t Controller::pollSensors()
{
	uint8_t sensorData = 0;

	xSemaphoreTake(mMutex, portMAX_DELAY);

	for (uint8_t i = 0; i < TRAFFIC_LIGHTS; i++)
		if (digitalRead(mTrafficLights[i].pin()))
			sensorData |= 1 << mTrafficLights[i].bitPosition();

	if (digitalRead(mPedestrianLight.pin()))
		sensorData |= 1 << mPedestrianLight.bitPosition();
	
	xSemaphoreGive(mMutex);
	return sensorData;
}

bool Controller::waitForButton()
{
	uint8_t count = 2;

	while (count) {
		if (digitalRead(mPedestrianLight.pin()) == LOW)
			return false;
		xSemaphoreGive(mMutex);
		vTaskDelay(10 / portTICK_PERIOD_MS);
		xSemaphoreTake(mMutex, portMAX_DELAY);
		count--;
	}

	return true;
}

void Controller::updatePriorities(uint8_t sensorData)
{
	BaseType_t priority;

	for (uint8_t i = 0; i < TRAFFIC_LIGHTS; i++) {
		if (sensorData & (1 << mTrafficLights[i].bitPosition()))
			priority = LightHighPriority;
		else
			priority = LightLowPriority;

		vTaskPrioritySet(mTrafficLights[i].task(), priority);
	}
}

bool Controller::isOnlyOneActive(uint8_t sensorData, uint8_t index) const
{
	return sensorData == 1 << index;
}
