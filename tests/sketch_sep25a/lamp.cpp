#include "lamp.h"

Lamp::Lamp(const Led *led, const unsigned char id) : led(led), id(id), run_sem(xSemaphoreCreateBinary()), halt_sem(xSemaphoreCreateBinary())
{
    if (run_sem == NULL || halt_sem == NULL)
        Serial.println("Algun semaforo en Lamp no se ha iniciado correctamente");
}

void Lamp::task(void *args)
{
    while (1)
    {
        led->red();
        if (xSemaphoreTake(run_sem, portMAX_DELAY) == pdTRUE)
        {
            led->green();
            if (xSemaphoreTake(halt_sem, portMAX_DELAY) == pdTRUE)
            {
                led->yellow();
                vTaskDelay(LAMP_YELLOW_LED_MS_TIME / portTICK_PERIOD_MS);
            }
            else
                Serial.println("No se adquirio el semaforo stop");
        }
        else
            Serial.println("No se adquirio el semaforo start");
    }
}

void Lamp::run()
{
    xSemaphoreGive(run_sem);
}

void Lamp::halt()
{
    xSemaphoreGive(halt_sem);
}

unsigned char Lamp::get_status()
{
    return led->get_status();
}

unsigned char Lamp::get_id()
{
    return id;
}

Lamp::~Lamp()
{
    //TODO no se como se utiliza.
}
