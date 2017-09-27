#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

template <class T, unsigned Capacity>
class CircularList
{
private:
	T *items[Capacity];
	unsigned index;
	unsigned dimension;

public:
	CircularList();
	T *next();
	T *prev();
	unsigned size() const;
	bool operator==(const CircularList<T, Capacity> &other) const;
	void add(T *item);
	void clear();
};


template <class T, unsigned Capacity>
CircularList<T, Capacity>::CircularList()
	: index(0),
	  dimension(0)
{

}

template <class T, unsigned Capacity>
T *CircularList<T, Capacity>::next()
{
	T *item = nullptr;

	item = items[index];
	if (dimension != 0)
		index = (index + 1) % dimension;

	return item;
}

template <class T, unsigned Capacity>
T *CircularList<T, Capacity>::prev()
{
	T *item = nullptr;

	item = items[index];
	if (dimension != 0)
		index = (index == 0) ? dimension - 1 : (index - 1);

	return item;
}

template <class T, unsigned Capacity>
inline unsigned CircularList<T, Capacity>::size() const
{
	return dimension;
}

template <class T, unsigned Capacity>
bool CircularList<T, Capacity>::operator==(const CircularList<T, Capacity> &other) const
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

template <class T, unsigned Capacity>
void CircularList<T, Capacity>::add(T *item)
{
	if (dimension < Capacity)
		items[dimension++] = item;
}

template <class T, unsigned Capacity>
void CircularList<T, Capacity>::clear()
{
	dimension = 0;
}

#endif
