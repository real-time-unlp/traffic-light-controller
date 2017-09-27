#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

template <class T, unsigned int N>
class CircularList
{
	private:
		T &items[];
		unsigned char index;

	public:
		Buffer();
		T &next();
		T &prev();
		unsigned char size();
		bool operator==(const Buffer &other);
		void add(Lamp &lamp);
		void clear();
		~Buffer();
};

#endif
