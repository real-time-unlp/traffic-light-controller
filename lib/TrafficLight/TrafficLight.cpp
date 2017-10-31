#pragma once
#include <TrafficLight.h>
#include <Arduino_FreeRTOS.h>
#include <Controller.h>

TrafficLight::TrafficLight(Controller &controller, uint8_t bitIndex, uint8_t greenDuration)
:	mController(controller),
	mBitIndex(bitIndex),
	mGreenDuration(greenDuration)
{
	xTaskCreate(runTask, "", configMINIMAL_STACK_SIZE, this, Controller::LightLowPriority, &mTask);
}