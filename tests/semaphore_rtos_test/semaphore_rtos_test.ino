#include <Arduino_FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <semphr.h>
#include "lamp.h"

#define sensor_pin 2

static void sensor_task(void *args);
static void semaphore_task(void *args);

static Lamp lamp(LED_BUILTIN);

void setup()
{
    Serial.begin(9600);
    while (!Serial);

    xTaskCreate(semaphore_task, "Semaphore", 128, NULL, 1, NULL);
    xTaskCreate(sensor_task, "Sensor", 128, NULL, 1, NULL);

    vTaskStartScheduler();
}

void loop()
{
}

void semaphore_task(void *args)
{
    lamp.task(args);
}

void sensor_task(void *args)
{
    unsigned char state = HIGH;
    unsigned char previousState = HIGH;

    pinMode(sensor_pin, INPUT);

    while (1)
    {
        state = digitalRead(sensor_pin);
        if (state != previousState)
        {
            if (state == HIGH)
            {
                lamp.turn_off();
                previousState = state;
            }
            else if (!lamp.is_on())
            {
                lamp.turn_on();
                previousState = state;
            }
        }
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}
