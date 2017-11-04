#pragma once
#include <stdint.h>
#include <Arduino_FreeRTOS.h>
#include <TrafficLight.h>
#include <semphr.h>
#include <LED.h>

class PedestrianLight : public TrafficLight {
public:
	PedestrianLight(LED &&led, uint8_t sensorPin, uint8_t index, uint16_t greenDuration);
	
protected:
	virtual void sense();
	virtual bool active() const;
	virtual void taskFunction(void *args);
	virtual bool hasToRun();

private:
	SemaphoreHandle_t mIdleSemaphore;
	SemaphoreHandle_t mActiveSem;
	
	TaskHandle_t mSensingTask;

	void release();
	
	void sensingTaskFunction(void *args);
	static void runSensingTask(void *instance)
	{
		reinterpret_cast<PedestrianLight*>(instance)->sensingTaskFunction(nullptr);
	};
};
