#include "led.h"

Led::Led(const unsigned char green_pin, const unsigned char yellow_pin, const unsigned char red_pin) : green_pin(green_pin), yellow_pin(yellow_pin), red_pin(red_pin)
{
    pinMode(this->green_pin, OUTPUT);
    digitalWrite(this->green_pin, LOW);
    pinMode(this->yellow_pin, OUTPUT);
    digitalWrite(this->yellow_pin, LOW);
    pinMode(this->red_pin, OUTPUT);
    digitalWrite(this->red_pin, LOW);
    this->led_status = OFF_STATUS;
}

void Led::on()
{
    red();
}

void Led::off()
{
    digitalWrite(green_pin, LOW);
    digitalWrite(yellow_pin, LOW);
    digitalWrite(red_pin, LOW);
    led_status = OFF_STATUS;
}

void Led::green()
{
    digitalWrite(green_pin, HIGH);
    digitalWrite(yellow_pin, LOW);
    digitalWrite(red_pin, LOW);
    led_status = GREEN_STATUS;
}

void Led::yellow()
{
    digitalWrite(green_pin, LOW);
    digitalWrite(yellow_pin, HIGH);
    digitalWrite(red_pin, LOW);
    led_status = YELLOW_STATUS;
}

void Led::red()
{
    digitalWrite(green_pin, LOW);
    digitalWrite(yellow_pin, LOW);
    digitalWrite(red_pin, HIGH);
    led_status = RED_STATUS;
}

unsigned char Led::get_status()
{
    return led_status;
}

Led::~Led()
{
    //TODO no se como se manejan los destructores.
}
