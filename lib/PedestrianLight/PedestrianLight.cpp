#include <PedestrianLight.h>
#include <Controller.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

PedestrianLight::PedestrianLight(LED &&led, Controller &controller, uint8_t sensorPin, SemaphoreHandle_t semaphore, uint16_t greenDuration)
: TrafficLight(static_cast<LED&&>(led), controller, sensorPin, semaphore, greenDuration),
  mIdleSemaphore(xSemaphoreCreateCounting(1, 1)),
  mMutex(xSemaphoreCreateCounting(1, 1)),
  mTouchedSem(xSemaphoreCreateCounting(1, 0)),
  mTouched(false)
{
	xTaskCreate(runSensingTask, "", configMINIMAL_STACK_SIZE, this, SensingTaskPriority, &mSensingTask);
	vTaskPrioritySet(mTask, HighPriority);
}

void PedestrianLight::taskFunction(void *args)
{
	while (true) {
		xSemaphoreTake(mTouchedSem, portMAX_DELAY);
		xSemaphoreTake(mSemaphore, portMAX_DELAY);
		mLED.green();
		vTaskDelay(mGreenDuration / portTICK_PERIOD_MS);
		mLED.red();
		vTaskDelay(RedLightDuration / portTICK_PERIOD_MS);

		mController.senseAll();
		release();
		xSemaphoreGive(mSemaphore);
		taskYIELD();
	}
}

void PedestrianLight::sensingTaskFunction(void *args)
{
	uint8_t count;
	while (true) {
		count = 3;
		while (count && digitalRead(mSensorPin)) {
			vTaskDelay(50 / portTICK_PERIOD_MS);
			count--;
		}

		if (count == 0) {
			xSemaphoreTake(mMutex, portMAX_DELAY);
			mTouched = true;
			xSemaphoreGive(mMutex);
			xSemaphoreGive(mTouchedSem);
			xSemaphoreTake(mIdleSemaphore, portMAX_DELAY);
		}
	}
}

void PedestrianLight::release()
{
	xSemaphoreTake(mMutex, portMAX_DELAY);
	mTouched = false;
	xSemaphoreGive(mMutex);
	xSemaphoreGive(mIdleSemaphore);
}

void PedestrianLight::sense()
{
	xSemaphoreTake(mMutex, portMAX_DELAY);
	if (mTouched)
		vTaskPrioritySet(mTask, HighPriority);
	else
		vTaskPrioritySet(mTask, LowPriority);
	xSemaphoreGive(mMutex);
}

bool PedestrianLight::active() const
{
	bool touched;
	xSemaphoreTake(mMutex, portMAX_DELAY);
	touched = mTouched;
	xSemaphoreGive(mMutex);
	return touched;
}
