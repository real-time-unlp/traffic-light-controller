#include "Sensor.h"
#include <Arduino.h>

Sensor::Sensor(uint8_t sensorPin, bool initialValue)
: sensorPin(sensorPin),
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
