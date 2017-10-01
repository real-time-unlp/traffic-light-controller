#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>

class System {
public:
	static constexpr uint8_t LAMP_PRIORITY = 3;
	static constexpr uint8_t CONTROLLER_PRIORITY = 2;
	static constexpr uint8_t SENSOR_MONITOR_PRIORITY = 1;
	static constexpr uint8_t MAX_LAMPS = 2;
	// En milisegundos
	static constexpr uint16_t YELLOW_DURATION = 500;
	static constexpr uint16_t TURN_DURATION = 1000;
	static constexpr uint16_t SENSOR_MONITOR_DURATION = 500;
	static constexpr uint16_t TRANSITION_TO_ANOTHER_LAMP = 1000;
};

#endif