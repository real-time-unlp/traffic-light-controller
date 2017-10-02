#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include <Lamp.h>

/*
 * Esta clase abstrae un sensor y su relación con una de las luces.
 */
class Sensor {
private:
	const uint8_t sensorPin;
	Lamp &mLamp;
	bool previousValue;
	bool currentValue;

public:
	Sensor(Lamp &lamp, uint8_t sensorPin, bool initialValue);
	void scan();
	bool value() const;
	Lamp &lamp() const;
};

#endif
