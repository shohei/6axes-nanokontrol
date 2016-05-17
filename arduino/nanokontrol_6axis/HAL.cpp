#include "HAL.h"
#include "Arduino.h"

#define _WRITE(port, v) do { if (v) {DIO ##  port ## _PORT -> PIO_SODR = DIO ## port ## _PIN; } else {DIO ##  port ## _PORT->PIO_CODR = DIO ## port ## _PIN; }; } while (0)

void HAL::setupTimer(){
  /* turn on the timer clock in the power management controller */
  pmc_set_writeprotect(false);		 // disable write protection for pmc registers
  pmc_enable_periph_clk(ID_TC7);	 // enable peripheral clock TC7
  /* we want wavesel 01 with RC */
  // TIMER_CLOCK1: 84Mhz/2 = 42.000 MHz
  // TIMER_CLOCK2: 84Mhz/8 = 10.500 MHz
  // TIMER_CLOCK3: 84Mhz/32 = 2.625 MHz
  // TIMER_CLOCK4: 84Mhz/128 = 656.250 KHz
  // TIMER_CLOCK5: SLCK ( slow clock )
  TC_Configure(/* clock */TC2,/* channel */1, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4); 
  //652.25 * 0.2(sec) = 131250
  TC_SetRC(TC2, 1, 131200);
  TC_Start(TC2, 1);
}

void HAL::startTimer(){

}