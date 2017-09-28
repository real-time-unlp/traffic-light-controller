#include <Arduino_FreeRTOS.h>
#include "Led.h"
#include "Lamp.h"

LED led(1,2,3);
Lamp lamp(led, 1);

void lamp_func(void* args);
void other_func(void *args);

void setup() {
	Serial.begin(9600);
	Serial.println("Todo en orden");
	
	xTaskCreate(lamp_func, "Lamp " + lamp.id(), 128, NULL, 2, NULL);
	xTaskCreate(other_func, "Other", 128, NULL, 1, NULL);

	vTaskStartScheduler();
}

void loop() {
}

void lamp_func(void *args) {
	lamp.task(args);
}

void other_func(void *args) {
	while(1) {
		lamp.go();
		Serial.println("Hola desde la otra funcion");
		vTaskDelay(10000 / portTICK_PERIOD_MS);
	}
}

