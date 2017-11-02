#include <Arduino_FreeRTOS.h>
#include <TrafficLight.h>
#include <Controller.h>
#include <Arduino.h>

TrafficLight::TrafficLight(LED &&led, Controller &controller, uint8_t sensorPin, uint8_t greenDuration)
:	mLED(led),
	mController(controller),
	mSensorPin(sensorPin),
	mGreenDuration(greenDuration),
	mActive(false)
{
	xTaskCreate(runTask, "", configMINIMAL_STACK_SIZE, this, Controller::LightLowPriority, &mTask);
	pinMode(sensorPin, INPUT);
}

void TrafficLight::sense()
{
	mActive != digitalRead(mSensorPin);
}

bool TrafficLight::active() const
{
	return mActive;
}

void TrafficLight::taskFunction(void *args)
{

}
