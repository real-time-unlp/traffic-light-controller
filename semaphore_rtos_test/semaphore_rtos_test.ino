#include <Arduino_FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <semphr.h>

static void semaphore_task(void *args);
static void serial_task(void *args);
static void sensor_task(void);

static volatile SemaphoreHandle_t startSem;
static volatile SemaphoreHandle_t stopSem;

static int sensor_pin = 2;

void setup() {
  //Serial.begin(9600);
  //while (!Serial);

  startSem = xSemaphoreCreateBinary();
  stopSem = xSemaphoreCreateBinary();

  attachInterrupt(digitalPinToInterrupt(sensor_pin), sensor_task, CHANGE);

  xTaskCreate(semaphore_task, "Semaphore", 128, NULL, 1, NULL);
  //xTaskCreate(serial_task, "Serial", 128, NULL, 1, NULL);

  vTaskStartScheduler();
}

void loop() {
}

void sensor_task(void) {
  unsigned char pressed = 0;

  if (digitalRead(sensor_pin) == LOW) { // Se detecto un auto.
    if (!pressed) {
      xSemaphoreGive(startSem);
      pressed = 1;
    }
  } else { // No hay mas autos en la calle.
    if (pressed) {
      xSemaphoreGive(stopSem);
      pressed = 0;
    }
  }

}

void serial_task(void *args) {
  byte value = 0;
  unsigned char pressed = 0;

  while (1) {
    value = Serial.read();
    if (value == 's') {
      if (!pressed) {
        xSemaphoreGive(startSem);
        pressed = 1;
      }
    } else if (value == 't') {
      if (pressed) {
        xSemaphoreGive(stopSem);
        pressed = 0;
      } else {
        Serial.println("El semaforo ya esta apagado");
      }
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void semaphore_task(void *args) {
  pinMode(LED_BUILTIN, OUTPUT);

  while (1) {
    digitalWrite(LED_BUILTIN, LOW);
    if (xSemaphoreTake(startSem, portMAX_DELAY) == pdTRUE) {
      Serial.println("Se adquirio semaforo start");
      digitalWrite(LED_BUILTIN, HIGH);
      if (xSemaphoreTake(stopSem, portMAX_DELAY) == pdTRUE) {
        Serial.println("Se adquirio semaforo stop");
        for (int i = 0; i < 5; i++) {
          digitalWrite(LED_BUILTIN, LOW);
          vTaskDelay(250 / portTICK_PERIOD_MS);
          digitalWrite(LED_BUILTIN, HIGH);
          vTaskDelay(250 / portTICK_PERIOD_MS);
        }
      } else {
        Serial.println("No se adquirio el semaforo stop");
      }
    } else {
      Serial.println("No se adquirio el semaforo start");
    }
  }
}

