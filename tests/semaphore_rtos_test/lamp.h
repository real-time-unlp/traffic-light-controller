#ifndef LAMP_H
#define LAMP_H

#include <Arduino_FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <semphr.h>
#include <Arduino.h>

class Lamp
{
private:
    volatile bool on;
    volatile SemaphoreHandle_t turn_on_sem;
    volatile SemaphoreHandle_t turn_off_sem;
    unsigned char led_pin;

public:
    Lamp(unsigned char led_pin);
    void task(void *args);
    void turn_on();
    void turn_off();
    bool is_on();
    ~Lamp();
};

#endif
