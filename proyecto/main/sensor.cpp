#include "sensor.h"

Sensor::Sensor(const unsigned char sensor_pin, const unsigned char default_value) : sensor_pin(sensor_pin)
{
	pinMode(sensor_pin, INPUT);
	this->current_state = default_value;
	this->previous_state = default_value;
}

void Sensor::scan()
{
	while (1)
	{
		current_state = digitalRead(sensor_pin);
		if (current_state != previous_state)
			previous_state = current_state;
	}
}

unsigned char Sensor::get_current_state()
{
	return current_state;
}

Sensor::~Sensor()
{
	//TODO no se que hacer
}
