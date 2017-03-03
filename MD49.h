#ifndef MD49_H
#define MD49_H

#include <Arduino.h>
#include <stdint.h>

template <typename Serial>
class MD49 {
public:
	MD49(Serial &p_serial)
		: serial(p_serial)
	{
		serial.begin(9600);
	}

	void step(void)
	{
		// Update speeds based on acceleration
		// Update encoders
		// Handle commands
	}

private:
	Serial &serial;
};

#endif
