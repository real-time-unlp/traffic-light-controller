#include <TrafficLight.h>
#include <Arduino_FreeRTOS.h>
#include <Controller.h>

TrafficLight::TrafficLight(Controller &controller, uint8_t bitPosition, uint8_t pin, uint8_t greenDuration)
:	mController(controller),
	mBitPosition(bitPosition),
	mGreenDuration(greenDuration)
	mTask(xTaskCreate(runTask, "", configMINIMAL_STACK_SIZE, this, Controller::LightLowPriority, &mTask))
{
}
