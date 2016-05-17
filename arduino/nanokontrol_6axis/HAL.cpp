#include "HAL.h"
#include "Arduino.h"
#include "Preference.h"

//increment current position
#define STEP_RESOLUTION 0.0001

// #define _WRITE(port, v) do { if (v) {DIO ##  port ## _PORT -> PIO_SODR = DIO ## port ## _PIN; } else {DIO ##  port ## _PORT->PIO_CODR = DIO ## port ## _PIN; }; } while (0)
#define _WRITE_NC(IO, v)  do { if (v) {DIO ##  IO ## _WPORT |= MASK(DIO ## IO ## _PIN); } else {DIO ##  IO ## _WPORT &= ~MASK(DIO ## IO ## _PIN); }; } while (0)

#define _WRITE_C(IO, v)   do { if (v) { \
                                         CRITICAL_SECTION_START; \
                                         {DIO ##  IO ## _WPORT |= MASK(DIO ## IO ## _PIN); }\
                                         CRITICAL_SECTION_END; \
                                       }\
                                       else {\
                                         CRITICAL_SECTION_START; \
                                         {DIO ##  IO ## _WPORT &= ~MASK(DIO ## IO ## _PIN); }\
                                         CRITICAL_SECTION_END; \
                                       }\
                                     }\
                                     while (0)
#define _WRITE(IO, v)  do {  if (&(DIO ##  IO ## _RPORT) >= (uint8_t *)0x100) {_WRITE_C(IO, v); } else {_WRITE_NC(IO, v); }; } while (0)
#define _READ(IO) ((bool)(DIO ## IO ## _RPORT & MASK(DIO ## IO ## _PIN)))

void HAL::setupTimer(void){
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
  //652.25 * 0.01(sec) = 131250
  // TC_SetRC(TC2, 1, 131200);
  // TC_SetRC(TC2, 1, 656250);//1sec
  TC_SetRC(TC2, 1, 6563);//0.01sec: 1000Hz
  TC_Start(TC2, 1);
}

void HAL::startTimer(void){
  TC2->TC_CHANNEL[1].TC_IER=TC_IER_CPCS;   // IER = interrupt enable register
  TC2->TC_CHANNEL[1].TC_IDR=~TC_IER_CPCS;  // IDR = interrupt disable register
  /* Enable the interrupt in the nested vector interrupt controller */
  /* TC4_IRQn where 4 is the timer number * timer channels (3) + the channel number (=(1*3)+1) for timer1 channel1 */
  NVIC_EnableIRQ(TC7_IRQn);
}

void HAL::CWStep(int dir, int step){
  // _WRITE(dir,false);
  // _WRITE(step,true);
  _DELAY_1_9_US;
  // _WRITE(step,false);
  _DELAY_1_9_US;
};

void HAL::CCWStep(int dir, int step){
  // _WRITE(dir,true);
  // _WRITE(step,true);
  _DELAY_1_9_US;
  // _WRITE(step,false);
  _DELAY_1_9_US;
};

//main loop
void TC7_Handler()
{
  TC_GetStatus(TC2, 1);
  Preference *state = Preference::getInstance();
  for(int i=0;i<6;i++){
      int _dest = state->motor[i].dest;
      int _cur = state->motor[i].cur;
      int _dir = state->motor[i].dirPin;
      int _step = state->motor[i].stepPin;
      if(_cur <_dest){
          HAL::CCWStep(_dir,_step);
      }else if(_cur > _dest){
          HAL::CWStep(_dir,_step);
      }
      state->motor[i].cur += STEP_RESOLUTION;
  }
  // TC_SetRC(TC2, 1, 656250);//1sec//debug
  TC_SetRC(TC2, 1, 6563);
}

