#ifndef SENSOR_MONITOR_H
#define SENSOR_MONITOR_H

#include <System.h>
#include <Array.h>
#include <Sensor.h>
#include <Controller.h>

class SensorMonitor {
private:
	Controller &controller;
	Array<Sensor, System::MAX_LAMPS> sensors;

public:
	SensorMonitor(Controller &controller, Array<Sensor, System::MAX_LAMPS> &sensors);
	void task(void *args);
};

#endif
