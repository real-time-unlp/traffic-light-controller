#ifndef BUFFER_H
#define BUFFER_H

#include <Arduino.h>
#include "config.h"

class Buffer
{
	private:
		const Lamp *lamps[];
		unsigned char size;
		unsigned char index;

	public:
		Buffer();
		*Lamp next(); //no se si tienen que ser punteros o copias, vos sabras.
		*Lamp prev(); //idem comentario del anterior.
		unsigned char get_size();
		bool equals(Buffer *other_buffer);
		void set(Lamp *lamps[]);
		void clear();
		~Buffer();
};

#endif
