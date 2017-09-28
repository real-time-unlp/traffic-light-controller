#include "Sensor.h"
#include <Arduino.h>

Sensor::Sensor(Lamp &lamp, uint8_t sensorPin, bool initialValue)
: mLamp(lamp),
  sensorPin(sensorPin),
  previousValue(initialValue),
  currentValue(initialValue)
{
	pinMode(sensorPin, INPUT);
}

void Sensor::scan()
{
	currentValue = digitalRead(sensorPin);
	if (currentValue != previousValue)
		previousValue = currentValue;
}

bool Sensor::value() const
{
	return currentValue;
}

Lamp &Sensor::lamp() const
{
	return mLamp;
}