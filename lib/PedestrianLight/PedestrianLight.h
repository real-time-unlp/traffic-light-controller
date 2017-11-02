#pragma once
#include <stdint.h>
#include <Arduino_FreeRTOS.h>
#include <../TrafficLight/TrafficLight.h>

class LED;
class Controller;

class PedestrianLight : public TrafficLight {
public:
	PedestrianLight(LED &&led, Controller &controller, uint8_t sensorPin, uint8_t greenDuration);
protected:
	TaskHandle_t mSensingTask;
	void taskFunction(void *args);
private:
	void sensingTaskFunction(void *args);
	SemaphoreHandle_t mMutex;
	bool mTouched;
	void release();

	static void runSensingTask(void *instance)
	{
		reinterpret_cast<PedestrianLight*>(instance)->sensingTaskFunction(nullptr);
	};
};
