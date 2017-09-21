#include "lamp.h"

Lamp::Lamp(unsigned char led_pin)
{
    on = false;

    this->led_pin = led_pin;
    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, LOW);

    turn_on_sem = xSemaphoreCreateBinary();
    turn_off_sem = xSemaphoreCreateBinary();
    if (turn_on_sem == NULL || turn_off_sem == NULL)
    {
        Serial.println("Algun semaforo en Lamp no se ha iniciado correctamente");
    }
}

void Lamp::task(void *args)
{
    while (1)
    {
        digitalWrite(led_pin, LOW);
        on = false;
        if (xSemaphoreTake(turn_on_sem, portMAX_DELAY) == pdTRUE)
        {
            digitalWrite(led_pin, HIGH);
            on = true;
            if (xSemaphoreTake(turn_off_sem, portMAX_DELAY) == pdTRUE)
            {
                for (int i = 0; i < 5; i++)
                {
                    digitalWrite(led_pin, LOW);
                    vTaskDelay(250 / portTICK_PERIOD_MS);
                    digitalWrite(led_pin, HIGH);
                    vTaskDelay(250 / portTICK_PERIOD_MS);
                }
            }
            else
                Serial.println("No se adquirio el semaforo stop");
        }
        else
            Serial.println("No se adquirio el semaforo start");
    }
}

void Lamp::turn_on()
{
    xSemaphoreGive(turn_on_sem);
}

void Lamp::turn_off()
{
    xSemaphoreGive(turn_off_sem);
}

bool Lamp::is_on()
{
    return on;
}

Lamp::~Lamp()
{
    vSemaphoreDelete(turn_on_sem);
    vSemaphoreDelete(turn_off_sem);
}
