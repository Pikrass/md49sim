#ifndef MD49_H
#define MD49_H

#include <Arduino.h>
#include <stdint.h>

#include "commands.h"

#define VERSION 1

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

	int8_t requested_speeds[2];

	void handle_command(void)
	{
		uint8_t command = serial.read();

		switch(command) {
			case MD49_CMD_GET_SPEED_1:
				serial.write(requested_speeds[0]);
				break;
			case MD49_CMD_GET_SPEED_2:
				serial.write(requested_speeds[1]);
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
				serial.write(24);
				break;
			case MD49_CMD_GET_CURRENT_1:
				serial.write(25);
				break;
			case MD49_CMD_GET_CURRENT_2:
				serial.write(25);
				break;
			case MD49_CMD_GET_VERSION:
				serial.write(VERSION);
				break;
			case MD49_CMD_GET_ACCELERATION:
				//TODO
				break;
			case MD49_CMD_GET_MODE:
				//TODO
				break;
			case MD49_CMD_GET_VI:
				serial.write(25);
				serial.write(10);
				serial.write(10);
				break;
			case MD49_CMD_GET_ERROR:
				serial.write(0);
				break;
			case MD49_CMD_SET_SPEED_1:
				requested_speeds[0] = serial.read();
				break;
			case MD49_CMD_SET_SPEED_2:
				requested_speeds[1] = serial.read();
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
