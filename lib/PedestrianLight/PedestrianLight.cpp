#include <PedestrianLight.h>
#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

PedestrianLight::PedestrianLight(LED &&led, uint8_t sensorPin, uint8_t index, uint16_t greenDuration)
: TrafficLight(static_cast<LED&&>(led), sensorPin, index, greenDuration),
  mIdleSemaphore(xSemaphoreCreateBinary()),
  mActiveSem(xSemaphoreCreateMutex())
{
	xTaskCreate(runSensingTask, "", configMINIMAL_STACK_SIZE, this, SensingTaskPriority, &mSensingTask);
}

void PedestrianLight::taskFunction(void *args)
{
	mLED.red();
	while (true) {
		xSemaphoreTake(mutex(), portMAX_DELAY);
		{
			if (hasToRun()) {
				mLED.green();
				vTaskDelay(mGreenDuration / portTICK_PERIOD_MS);
				for (uint8_t i = 0; i < 3; i++) {
					mLED.off();
					vTaskDelay(500 / portTICK_PERIOD_MS);
					mLED.yellow();
					vTaskDelay(500 / portTICK_PERIOD_MS);
				}
				mLED.red();
				vTaskDelay(RedLightDuration / portTICK_PERIOD_MS);
				release();
				senseAll();
			}
		}
		xSemaphoreGive(lights[mNextIndex]->mutex());
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
			xSemaphoreTake(mActiveSem, portMAX_DELAY);
			mActive = true;
			xSemaphoreGive(mActiveSem);
			xSemaphoreTake(mIdleSemaphore, portMAX_DELAY);
		}
	}
}

void PedestrianLight::release()
{
	xSemaphoreTake(mActiveSem, portMAX_DELAY);
	mActive = false;
	xSemaphoreGive(mActiveSem);
	xSemaphoreGive(mIdleSemaphore);
}

void PedestrianLight::sense()
{
	return;
}

bool PedestrianLight::hasToRun()
{
	return active();
}

bool PedestrianLight::active() const
{
	bool touched;
	xSemaphoreTake(mActiveSem, portMAX_DELAY);
	touched = mActive;
	xSemaphoreGive(mActiveSem);
	return touched;
}
