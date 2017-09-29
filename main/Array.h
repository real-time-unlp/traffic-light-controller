#ifndef ARRAY_H
#define ARRAY_H

#include <stdint.h>
#include <Arduino.h>

template<typename T, unsigned Capacity>
class Array {
	T elements[Capacity];
public:
	Array(T elem[Capacity])
	: elements(elem)
	{
	};
	virtual ~Array() = default;
	Array(const Array&) = default;
	// Muy antituitivamente, esto denota una referencia a un array.
	// No una array de referencias.
	Array(T (&&elem)[Capacity])
	: elements(elem)
	{
	};
	Array &operator=(const Array&) = default;
	Array &operator=(Array&&) = default;
	T &operator[](uint8_t index)
	{
		if (index >= Capacity)
			Serial.write("Array: acceso fuera de rango.");
		return elements[index];
	}
	uint8_t size() const
	{
		return Capacity;
	}
};

#endif
