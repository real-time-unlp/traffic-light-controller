#pragma once
#include <stdint.h>
#include <Arduino_FreeRTOS.h>
#include <LED.h>
#include <semphr.h>
#include <task.h>

class TrafficLight {
public:
	TrafficLight(LED &&led, uint8_t sensorPin, uint8_t index, uint16_t greenDuration);

	static constexpr uint8_t AMOUNT = 5;

	static constexpr BaseType_t TrafficLightPriority = 2;
	static constexpr BaseType_t SensingTaskPriority = 1;

	static constexpr TickType_t GreenAvenueDuration = 1000;
	static constexpr TickType_t YellowLightDuration = 500;
	static constexpr TickType_t RedLightDuration = 500;

	SemaphoreHandle_t mutex() const;
	static TrafficLight *lights[AMOUNT];
	
protected:
	static volatile uint8_t activesCount;

	void senseAll();
	virtual void sense();
	virtual bool active() const;
	virtual bool hasToRun();
	
	virtual void taskFunction(void *args);
	static void runTask(void *instance)
	{
		reinterpret_cast<TrafficLight*>(instance)->taskFunction(nullptr);
	};
	
	LED mLED;
	const volatile uint8_t mSensorPin;
	const volatile uint8_t mNextIndex;
	const volatile uint16_t mGreenDuration;
	TaskHandle_t mTask;
	const volatile SemaphoreHandle_t mMutex;
	volatile bool mActive;

private:
	bool isOnlyOneActive();
};
