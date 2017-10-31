#pragma once
#include <stdint.h>
#include <Arduino_FreeRTOS.h>

class Controller;

class TrafficLight {
public:
	TrafficLight(Controller &controller, uint8_t bitIndex, uint8_t greenDuration);

	TaskHandle_t task()
	{
		return mTask;
	}	
private:
	Controller &mController;
	const uint8_t mBitIndex;
	const uint8_t mGreenDuration;
	TaskHandle_t mTask;
	void taskFunction(void *args);

	static void runTask(void *instance)
	{
		reinterpret_cast<TrafficLight*>(instance)->taskFunction(nullptr);
	};
};
