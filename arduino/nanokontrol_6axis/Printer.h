#ifndef _PRINTER_H
#define _PRINTER_H

#include "Preference.h"

class Printer {
public:
	static void initState();
	static void setOrigin(int motorNumber);
	static void setOffsetToDestination(int motorNumber);
	static void checkEndstop(int motorNumber);
	static void homing();
	static void setupStepperMotor();
	static void doJog(int jog_command_number);
	static void updateRingBufferIndex(Preference* state, int i, int jog_or_slider, bool direction, const char* dests[]);
};

#endif