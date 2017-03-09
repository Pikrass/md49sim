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
		: serial(p_serial), awaiting_cmd(false), accel(5)
	{
		serial.begin(9600);
	}

	void step(void)
	{
		// Update speeds based on acceleration
		// Update encoders

		while (serial.available()) {
			if (!awaiting_cmd) {
				if (serial.read() == MD49_SYNC)
					awaiting_cmd = true;
				continue;
			}

			handle_command();
			awaiting_cmd = false;
		}
	}

private:
	Serial &serial;

	bool awaiting_cmd;

	int8_t requested_speeds[2];
	uint8_t accel;

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
				serial.write(accel);
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
				accel = serial.read();
				if (accel < 1)
					accel = 1;
				else if (accel > 10)
					accel = 10;
				break;
			case MD49_CMD_SET_MODE:
				//TODO
				break;
			case MD49_CMD_RESET_ENCODERS:
				//TODO
				break;
			case MD49_CMD_DISABLE_REGULATOR:
				break;
			case MD49_CMD_ENABLE_REGULATOR:
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
