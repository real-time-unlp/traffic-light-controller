#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor
{
private:
	const unsigned char sensor_pin;
	unsigned char previous_state;
	unsigned char current_state;

public:
	Sensor(const unsigned char sensor_pin, const unsigned char default_value);
	void scan();
	unsigned char get_current_state();
	~Sensor();
};

#endif
