#pragma once
#include <stdint.h>
#include <Arduino_FreeRTOS.h>

class Controller;

class PedestrianLight {
public:
	PedestrianLight(Controller &controller, uint8_t greenLightDuration);
	TaskHandle_t task()
	{
		return mTask;
	}

private:
	Controller &mController;
	TaskHandle_t mTask;

	void taskFunction(void *args);

	static void runTask(void *instance)
	{
		reinterpret_cast<PedestrianLight*>(instance)->taskFunction(NULL);
	};
};
