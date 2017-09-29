#include "SensorMonitor.h"
#include <Arduino_FreeRTOS.h>

SensorMonitor::SensorMonitor(Controller &controller, Array<Sensor, System::MAX_LAMPS> &sensors)
: controller(controller),
  sensors(sensors)
{
}

void SensorMonitor::task(void *args)
{
	while(1) {
		for(int i = 0; i < sensors.size(); i++) {
			sensors[i].scan();
		}
		controller.receive(sensors);
		vTaskDelay(System::SENSOR_MONITOR_DURATION / portTICK_PERIOD_MS);
	}
}
