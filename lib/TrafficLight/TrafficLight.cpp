#include <Arduino_FreeRTOS.h>
#include <TrafficLight.h>
#include <Arduino.h>

volatile uint8_t TrafficLight::activesCount = 0;
TrafficLight *TrafficLight::lights[TrafficLight::AMOUNT] = {};

TrafficLight::TrafficLight(LED &&led, uint8_t sensorPin, uint8_t sensorActiveHigh, uint8_t index, uint16_t greenDuration)
:	mLED(led),
	mSensorPin(sensorPin),
	mNextIndex((index + 1) % AMOUNT),
	mGreenDuration(greenDuration),
	mMutex(xSemaphoreCreateBinary())
{
	mActive = false;
	mSensorActiveHigh = sensorActiveHigh;
	xTaskCreate(runTask, "", configMINIMAL_STACK_SIZE, this, TrafficLightPriority, &mTask);
	pinMode(sensorPin, INPUT);
	mLED.off();
}

void TrafficLight::senseAll()
{
	activesCount = 0;
	for(int i = 0; i < AMOUNT; i++) {
		TrafficLight &light = *lights[i];
		light.sense();
		if (light.active())
			++activesCount;
	}
}

void TrafficLight::sense()
{
	mActive = (digitalRead(mSensorPin) == mSensorActiveHigh);
}

bool TrafficLight::active() const
{
	return mActive;
}

void TrafficLight::taskFunction(void *args)
{
	TickType_t greenTime;
	mLED.red();
	while(1) {
		greenTime = mGreenDuration;
		xSemaphoreTake(mutex(), portMAX_DELAY); {
			if (hasToRun()) {
				do {
					mLED.green();
					vTaskDelay(greenTime / portTICK_PERIOD_MS);
					//greenTime = (greenTime - 5000 > 15000) ? greenTime - 5000 : 15000;
					senseAll();
				} while(isOnlyOneActive());
				mLED.yellow();
				vTaskDelay(YellowLightDuration / portTICK_PERIOD_MS);
				mLED.red();
				vTaskDelay(RedLightDuration / portTICK_PERIOD_MS);
			}
		}
		xSemaphoreGive(lights[mNextIndex]->mutex());
	}
}

bool TrafficLight::hasToRun()
{
	return active() || activesCount == 0;
}

bool TrafficLight::isOnlyOneActive()
{
	return active() && activesCount == 1;
}

SemaphoreHandle_t TrafficLight::mutex() const
{
	return mMutex;
}