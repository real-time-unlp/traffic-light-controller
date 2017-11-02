#pragma once
#include <stdint.h>
#include <Arduino_FreeRTOS.h>
#include <LED.h>

class Controller;


class TrafficLight {
public:
	TrafficLight(LED &&led, Controller &controller, uint8_t sensorPin,
			SemaphoreHandle_t semaphore, uint8_t greenDuration);

	TaskHandle_t task()
	{
		return mTask;
	};

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

	LED mLED;
	Controller &mController;
	const uint8_t mSensorPin;
	const uint8_t mGreenDuration;
	TaskHandle_t mTask;
	SemaphoreHandle_t mSemaphore;
private:
	bool mActive;
};
