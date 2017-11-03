#pragma once
#include <stdint.h>
#include <Arduino_FreeRTOS.h>
#include <LED.h>
#include <semphr.h>

class Controller;


class TrafficLight {
public:
	TrafficLight(LED &&led, Controller &controller, uint8_t sensorPin,
			SemaphoreHandle_t semaphore, uint16_t greenDuration);

	static constexpr BaseType_t MaxPriority = 4;
	static constexpr BaseType_t HighPriority = 3;
	static constexpr BaseType_t LowPriority = 2;
	static constexpr BaseType_t SensingTaskPriority = 1;

	static constexpr uint16_t GreenAvenueDuration = 1000;
	static constexpr uint16_t YellowLightDuration = 500;
	static constexpr uint16_t RedLightDuration = 500;

	uint8_t sensorPin()
	{
		return mSensorPin;
	};

	/*
	 * Realiza la lectura para determinar si está activo o no y cambia la
	 * prioridad de su tarea.
	 */
	virtual void sense();

	// Devuelve el resultado de lo realizado por sense()
	virtual bool active() const;
protected:

	virtual void taskFunction(void *args);

	static void runTask(void *instance)
	{
		reinterpret_cast<TrafficLight*>(instance)->taskFunction(nullptr);
	};

	void senseAndUpdatePriorities();

	LED mLED;
	Controller &mController;
	const uint8_t mSensorPin;
	const uint16_t mGreenDuration;
	TaskHandle_t mTask;
	SemaphoreHandle_t mSemaphore;
private:
	bool mActive;
};
