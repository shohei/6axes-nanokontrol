#ifndef _HAL_H
#define _HAL_H

#include <stdint.h>

#define F_CPU       21000000        // should be factor of F_CPU_TRUE
#define F_CPU_TRUE  84000000        // actual CPU clock frequency

//delay1.9us: 155cycle(NOP): 84MHz
// #define _DELAY_1_9_US __asm__ __volatile__ ("nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"); 
//improved: delay1.9us: 147cycle(NOP): 84MHz: with IO writing overhead
#define _DELAY_1_9_US __asm__ __volatile__ ("nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"); 

class HAL{
public:
    HAL();
    virtual ~HAL();
    static void setupTimer();
    static void startTimer();
    static void doSendDirection(int motorNumber, bool isClockWise);
    static void doSendPulse(int motorNumber);
    static void setupStepperMotor();
    static void homing();
};


#endif