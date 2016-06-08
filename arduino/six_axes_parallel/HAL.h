#ifndef _HAL_H
#define _HAL_H

#include <stdint.h>
#include "fastio.h"
#include "Arduino.h"
#include "Preference.h"
#include "Configuration.h"
#include "Printer.h"

// #define F_CPU       21000000        // should be factor of F_CPU_TRUE
// #define F_CPU_TRUE  84000000        // actual CPU clock frequency

//delay1.9us: 155cycle(NOP): 84MHz
// #define _DELAY_1_9_US __asm__ __volatile__ ("nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"); 
//improved: delay1.9us: 147cycle(NOP): 84MHz: with IO writing overhead
#define _DELAY_1_9_US __asm__ __volatile__ ("nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"" nop\n\t"); 

#define _WRITE(port, v)     do { if (v) {DIO ##  port ## _PORT -> PIO_SODR = DIO ## port ## _PIN; } else {DIO ##  port ## _PORT->PIO_CODR = DIO ## port ## _PIN; }; } while (0)
#define WRITE(pin,v) _WRITE(pin,v)
#define _READ(pin) (DIO ##  pin ## _PORT->PIO_PDSR & DIO ##  pin ## _PIN ? 1 : 0) // does return 0 or pin value
#define READ(pin) _READ(pin)

#define _GET_STEP_PIN(pin) M ## pin ## _STEP_PIN
#define GET_STEP_PIN(pin) _GET_STEP_PIN(pin)

#define _GET_DIR_PIN(pin) M ## pin ## _DIR_PIN
#define GET_DIR_PIN(pin) _GET_DIR_PIN(pin)

#define _GET_ENABLE_PIN(pin) M ## pin ## _ENABLE_PIN
#define GET_ENABLE_PIN(pin) _GET_ENABLE_PIN(pin)

#define _GET_MIN_PIN(pin) M ## pin ## _MIN_PIN
#define GET_MIN_PIN(pin) _GET_MIN_PIN(pin)

#define SET_INPUT(pin) pmc_enable_periph_clk(g_APinDescription[pin].ulPeripheralId); \
  PIO_Configure(g_APinDescription[pin].pPort, PIO_INPUT, g_APinDescription[pin].ulPin, 0)
#define SET_OUTPUT(pin) PIO_Configure(g_APinDescription[pin].pPort, PIO_OUTPUT_1, \
    g_APinDescription[pin].ulPin, g_APinDescription[pin].ulPinConfiguration)


class HAL{
  public:
    HAL();
    virtual ~HAL();
    static void setupTimer();
    static void startTimer();
    static void doSendDirection(int motorNumber, bool isClockWise);
    static void doSendPulse(int motorNumber);
};


#endif
