#include <Arduino_FreeRTOS.h>
#include <TrafficLight.h>
#include <Controller.h>
#include <Arduino.h>

TrafficLight::TrafficLight(LED &&led, Controller &controller, uint8_t sensorPin, SemaphoreHandle_t semaphore, uint16_t greenDuration)
:	mLED(led),
	mController(controller),
	mSensorPin(sensorPin),
	mGreenDuration(greenDuration),
	mSemaphore(semaphore)
{
	mActive = false;
	xTaskCreate(runTask, "", configMINIMAL_STACK_SIZE, this, Controller::LightLowPriority, &mTask);
	pinMode(sensorPin, INPUT);
	mLED.off();
}

void TrafficLight::sense()
{
	mActive = (digitalRead(mSensorPin) == LOW);
	if (mActive)
		vTaskPrioritySet(mTask, Controller::LightHighPriority);
	else
		vTaskPrioritySet(mTask, Controller::LightLowPriority);
}

bool TrafficLight::active() const
{
	return mActive;
}

void TrafficLight::taskFunction(void *args)
{
	uint16_t greenTime;
	mLED.red();
	while(1) {
		greenTime = mGreenDuration;
		xSemaphoreTake(mSemaphore, portMAX_DELAY); {
			do {
				mLED.green();
				vTaskDelay(greenTime / portTICK_PERIOD_MS);
				//greenTime = (greenTime - 5 > 15) ? greenTime - 5 : 15;
				mController.senseAll();
			} while(mController.isOnlyOneActive(*this));
			mLED.yellow();
			vTaskDelay(Controller::YellowLightDuration / portTICK_PERIOD_MS);
			mLED.red();
			vTaskDelay(Controller::RedLightDuration / portTICK_PERIOD_MS);
		}
		xSemaphoreGive(mSemaphore);
		taskYIELD();
	}
}
