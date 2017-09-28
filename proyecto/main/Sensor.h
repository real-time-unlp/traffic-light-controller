#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>

class Sensor
{
private:
	const uint8_t sensorPin;
	bool previousValue;
	bool currentValue;

public:
	Sensor(uint8_t sensorPin, bool initialValue);
	void scan();
	bool value() const;
};

#endif
