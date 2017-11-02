#pragma once
#include <stdint.h>
#include <Arduino_FreeRTOS.h>

class Controller;

class TrafficLight {
public:
	TrafficLight(Controller &controller, uint8_t bitIndex, uint8_t sensorPin, uint8_t greenDuration);

	TaskHandle_t task()
	{
		return mTask;
	};

	uint8_t sensorPin()
	{
		return mSensorPin;
	};

	uint8_t bitPosition()
	{
		return mBitPosition;
	};

private:
	Controller &mController;
	const uint8_t mBitPosition;
	const uint8_t mSensorPin;
	const uint8_t mGreenDuration;
	TaskHandle_t mTask;
	virtual void taskFunction(void *args);

	static void runTask(void *instance)
	{
		reinterpret_cast<TrafficLight*>(instance)->taskFunction(nullptr);
	};
};
