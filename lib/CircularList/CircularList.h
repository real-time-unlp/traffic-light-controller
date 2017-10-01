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
	CircularList<T, Capacity> volatile &operator=(const volatile CircularList<T, Capacity> &other) volatile
	{
		this->index = other.index;
		this->dimension = other.dimension;
		for (uint8_t i = 0; i < dimension; i++) {
			this->items[i] = other.items[i];
		}
		return *this;
	};

	T *next() volatile
	{
		T *item = nullptr;

		item = items[index];
		if (dimension != 0)
			index = (index + 1) % dimension;

		return item;
	}

	T *prev() volatile
	{
		T *item = nullptr;

		item = items[index];
		if (dimension != 0)
			index = (index == 0) ? dimension - 1 : (index - 1);

		return item;
	}

	T *current() volatile
	{
		return items[index];
	}

	unsigned size() const volatile
	{
		return dimension;
	};

	bool operator==(const volatile CircularList<T, Capacity> &other) const volatile
	{
		if (size() != other.size())
			return false;

		bool equal = true;
		for (uint8_t i = 0; i < dimension && equal; i++) {
			bool found = false;
			for (uint8_t j = 0; j < dimension && !found; j++) {
				if (items[i] == other.items[j])
					found = true;
			}
			equal = found;
		}
		// Si |A| = |B| y  A está contenido en B --> A = B
		return equal;
	}

	bool operator!=(const volatile CircularList<T, Capacity> &other) const volatile
	{
		return !(*this == other);
	}

	void add(T *item) volatile
	{
		if (dimension < Capacity)
			items[dimension++] = item;
	}

	void clear() volatile
	{
		dimension = 0;
	}
};

#endif
