#include <PedestrianLight.h>
#include <Controller.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

PedestrianLight::PedestrianLight(LED &&led, Controller &controller, uint8_t sensorPin,
				SemaphoreHandle_t semaphore ,uint8_t greenDuration)
: TrafficLight(static_cast<LED&&>(led), controller, sensorPin, semaphore, greenDuration),
  mMutex(xSemaphoreCreateCounting(1, 1)),
  mTouched(false)
{
	xTaskCreate(	runSensingTask,
			"",
			configMINIMAL_STACK_SIZE,
			this,
			Controller::LightLowPriority,
			&mSensingTask);
}

void PedestrianLight::taskFunction(void *args)
{
	while (true) {
		xSemaphoreTake(mSemaphore, portMAX_DELAY);
		mLED.green();
		vTaskDelay(mGreenDuration / portTICK_PERIOD_MS);
		mLED.red();
		vTaskDelay(Controller::RedLightDuration / portTICK_PERIOD_MS);

		mController.senseAll();
		xSemaphoreGive(mSemaphore);
	}
}

void PedestrianLight::sensingTaskFunction(void *args)
{
	uint8_t count;
	while (true) {
		count = 3;
		while (digitalRead(mSensorPin))
			count--;

		if (count == 0) {
			xSemaphoreTake(mMutex, portMAX_DELAY);
			mTouched = true;
			xSemaphoreGive(mMutex);
			// podria dormirse hasta que se haga release() o algo
		}

		vTaskDelay(50 / portTICK_PERIOD_MS);
	}
}

void PedestrianLight::release()
{
	xSemaphoreTake(mMutex, portMAX_DELAY);
	mTouched = false;
	xSemaphoreGive(mMutex);
}
