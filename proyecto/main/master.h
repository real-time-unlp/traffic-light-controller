#ifndef MASTER_H
#define MASTER_H

#include <Arduino_FreeRTOS.h>
#include <semphr.h>
#include "circular_list.h"

class Master
{
	private:
		circular_list actives; //TODO como especifico el template.
		circular_list disabled; //idem.
		const volatile SemaphoreHandle_t changes_sem;

	public:
		Master(const circular_list actives, const circular_list disabled);
		void task(void *args);
		void send(const circular_list actives, const circular_list disabled);
		~Master();
};

#endif