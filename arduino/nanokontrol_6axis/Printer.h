#ifndef _PRINTER_H
#define _PRINTER_H

class Printer {
public:
	static void setOrigin(int motorNumber);
	static void setOffsetToDestination(int motorNumber);
	static void checkEndstop(int motorNumber);
    static void homing();
    static void setupStepperMotor();
};

#endif