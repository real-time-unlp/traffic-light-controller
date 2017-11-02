#include <Arduino_FreeRTOS.h>
#include <TrafficLight.h>
#include <Controller.h>

TrafficLight::TrafficLight(LED &&led, Controller &controller, uint8_t sensorPin, uint8_t greenDuration)
:	mLED(led),
	mController(controller),
	mSensorPin(sensorPin),
	mGreenDuration(greenDuration)
{
	xTaskCreate(runTask, "", configMINIMAL_STACK_SIZE, this, Controller::LightLowPriority, &mTask);
}
