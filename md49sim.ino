#include <Arduino.h>

#include "MD49.h"

MD49<HardwareSerial> *md49;

void setup()
{
	while(!Serial);
	md49 = new MD49<HardwareSerial>(Serial);
}

void loop()
{
	md49->step();
	delay(16);
}
