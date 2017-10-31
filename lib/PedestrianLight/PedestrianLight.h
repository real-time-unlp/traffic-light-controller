#pragma once
#include <stdint.h>
#include <Arduino_FreeRTOS.h>

class Controller;

class PedestrianLight {
public:
	PedestrianLight(Controller &controller, uint8_t GreenLightDuration);
	TaskHandle_t task()
	{
		return mTask;
	}

private:
	Controller &mController;
	TaskHandle_t mTask;

	void taskFunction(void *args);

	static void runTask(void *instance, void *args)
	{
		reinterpret_cast<PedestrianLight*>(instance)->taskFunction(args);
	};
};
