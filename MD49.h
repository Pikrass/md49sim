#ifndef MD49_H
#define MD49_H

#include <Arduino.h>
#include <stdint.h>

#include "commands.h"

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

		while (serial.available())
			handle_command();
	}

private:
	Serial &serial;

	void handle_command(void)
	{
		uint8_t command = serial.read();

		switch(command) {
			case MD49_CMD_GET_SPEED_1:
				//TODO
				break;
			case MD49_CMD_GET_SPEED_2:
				//TODO
				break;
			case MD49_CMD_GET_ENCODER_1:
				//TODO
				break;
			case MD49_CMD_GET_ENCODER_2:
				//TODO
				break;
			case MD49_CMD_GET_ENCODERS:
				//TODO
				break;
			case MD49_CMD_GET_VOLTS:
				//TODO
				break;
			case MD49_CMD_GET_CURRENT_1:
				//TODO
				break;
			case MD49_CMD_GET_CURRENT_2:
				//TODO
				break;
			case MD49_CMD_GET_VERSION:
				//TODO
				break;
			case MD49_CMD_GET_ACCELERATION:
				//TODO
				break;
			case MD49_CMD_GET_MODE:
				//TODO
				break;
			case MD49_CMD_GET_VI:
				//TODO
				break;
			case MD49_CMD_GET_ERROR:
				//TODO
				break;
			case MD49_CMD_SET_SPEED_1:
				//TODO
				break;
			case MD49_CMD_SET_SPEED_2:
				//TODO
				break;
			case MD49_CMD_SET_ACCELERATION:
				//TODO
				break;
			case MD49_CMD_SET_MODE:
				//TODO
				break;
			case MD49_CMD_RESET_ENCODERS:
				//TODO
				break;
			case MD49_CMD_DISABLE_REGULATOR:
				//TODO
				break;
			case MD49_CMD_ENABLE_REGULATOR:
				//TODO
				break;
			case MD49_CMD_DISABLE_TIMEOUT:
				//TODO
				break;
			case MD49_CMD_ENABLE_TIMEOUT:
				//TODO
				break;
			default:
				break;
		}
	}
};

#endif
