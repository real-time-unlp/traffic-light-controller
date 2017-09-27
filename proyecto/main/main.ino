#include <Arduino_FreeRTOS.h>
#include "led.h"
#include "lamp.h"

const Led led(1,2,3);
const Lamp lamp(&led, 1);

void lamp_func(void* args);
void other_func(void *args);

void setup() {
	Serial.begin(9600);
	Serial.println("Todo en orden");
	
	xTaskCreate(lamp_func, "Lamp " + lamp.get_id(), 128, NULL, 2, NULL);
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
		lamp.run();
		Serial.println("Hola desde la otra funcion");
		vTaskDelay(10000 / portTICK_PERIOD_MS);
	}
}

