#include <TrafficLight.h>
#include <Arduino_FreeRTOS.h>
#include <Controller.h>

TrafficLight::TrafficLight(Controller &controller, uint8_t bitPosition, uint8_t sensorPin, uint8_t greenDuration)
:	mController(controller),
	mBitPosition(bitPosition),
	mSensorPin(sensorPin),
	mGreenDuration(greenDuration)
{
	xTaskCreate(runTask, "", configMINIMAL_STACK_SIZE, this, Controller::LightLowPriority, &mTask);
}
