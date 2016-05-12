#ifndef _STEPPER_H
#define _STEPPER_H


#define _WRITE(port, v) do { if (v) {DIO ##  port ## _PORT -> PIO_SODR = DIO ## port ## _PIN; } else {DIO ##  port ## _PORT->PIO_CODR = DIO ## port ## _PIN; }; } while (0)

static void genStepPulse(int motorNumber, bool isHigh){
	int port = Preference.motor[i].port;
	if(isHigh){
		//TODO
	}else{
		//TODO
	}
}


#endif