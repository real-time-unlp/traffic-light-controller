#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>
#include <Arduino.h>

template<typename T, unsigned Capacity>
class Array {
	T elements[Capacity];
	uint8_t mSize = 0;
public:
	Array() = default;
	virtual ~Array() = default;
	Array(const Array&) = default;
	Array(Array&&) = default;
	Array &operator=(const Array&) = default;
	Array &operator=(Array&&) = default;
	T &operator[](uint8_t index)
	{
		if (index >= mSize)
			Serial.write("Array: acceso fuera de rango.");
		return elements[index];
	}
	uint8_t size const()
	{
		return mSize;
	}
};

#endif
