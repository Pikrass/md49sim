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
		: serial(p_serial), awaiting_cmd(false), accel(5), timeout(true)
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

			last_comm = millis();
			handle_command();
			awaiting_cmd = false;
		}
	}

private:
	Serial &serial;

	bool awaiting_cmd;

	int8_t requested_speeds[2];
	uint8_t accel;
	int16_t encoders[2];
	bool timeout;
	unsigned long last_comm;

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
				send_encoder(0);
				break;
			case MD49_CMD_GET_ENCODER_2:
				send_encoder(1);
				break;
			case MD49_CMD_GET_ENCODERS:
				send_encoder(0);
				send_encoder(1);
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
				encoders[0] = 0;
				encoders[1] = 0;
				break;
			case MD49_CMD_DISABLE_REGULATOR:
				break;
			case MD49_CMD_ENABLE_REGULATOR:
				break;
			case MD49_CMD_DISABLE_TIMEOUT:
				timeout = false;
				break;
			case MD49_CMD_ENABLE_TIMEOUT:
				timeout = true;
				break;
			default:
				break;
		}
	}

	void send_encoder(int i)
	{
		/* Encoders are 32 bits according to documentation, but 16 bits
		 * according to reality
		 */

		if (encoders[i] >= 0) {
			serial.write(0x00);
			serial.write(0x00);
		} else {
			serial.write(0xff);
			serial.write(0xff);
		}

		for (int b = 1 ; b >= 0 ; --b) {
			int8_t byte = encoders[i] >> 8*b;
			serial.write(byte);
		}
	}
};

#endif
