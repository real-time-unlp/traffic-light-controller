#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <stdint.h>

template <class T, uint8_t Capacity>
class CircularList {
private:
	T *items[Capacity];
	uint8_t index = 0;
	uint8_t dimension = 0;

public:
	CircularList() = default;

	T *next()
	{
		T *item = nullptr;

		item = items[index];
		if (dimension != 0)
			index = (index + 1) % dimension;

		return item;
	}

	T *prev()
	{
		T *item = nullptr;

		item = items[index];
		if (dimension != 0)
			index = (index == 0) ? dimension - 1 : (index - 1);

		return item;
	}

	unsigned size() const
	{
		return dimension;
	};

	bool operator==(const CircularList<T, Capacity> &other) const
	{
		if (size() != other.size())
			return false;

		bool equal = true;
		for (unsigned i = 0; i < dimension; i++) {
			if (items[i] != other.items[i]) {
				equal = false;
				break;
			}
		}
		return equal;
	}

	bool operator!=(const CircularList<T, Capacity> &other) const
	{
		return !(*this == other);
	}

	void add(T *item)
	{
		if (dimension < Capacity)
			items[dimension++] = item;
	}

	void clear()
	{
		dimension = 0;
	}
};

#endif
