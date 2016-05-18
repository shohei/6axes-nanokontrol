#include "HAL.h"
#include "Arduino.h"
#include "Preference.h"
#include "Configuration.h"
#include "fastio.h"

//increment current position
#define STEP_RESOLUTION 1 

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

#define CW  true
#define CCW false

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
  // TC_SetRC(TC2, 1, 6563);//0.01sec: 100Hz
  // TC_SetRC(TC2, 1, 656);//0.001sec: 1000Hz
  TC_SetRC(TC2, 1, 65);
  TC_Start(TC2, 1);
}

void HAL::startTimer(void){
  TC2->TC_CHANNEL[1].TC_IER=TC_IER_CPCS;   // IER = interrupt enable register
  TC2->TC_CHANNEL[1].TC_IDR=~TC_IER_CPCS;  // IDR = interrupt disable register
  /* Enable the interrupt in the nested vector interrupt controller */
  /* TC4_IRQn where 4 is the timer number * timer channels (3) + the channel number (=(1*3)+1) for timer1 channel1 */
  NVIC_EnableIRQ(TC7_IRQn);
}

void HAL::doSendDirection(int motorNumber, bool isClockWise){
  if(isClockWise){
    switch(motorNumber){
      case 0:
      WRITE(GET_DIR_PIN(1),true);
      break;    
      case 1:
      WRITE(GET_DIR_PIN(2),true);
      break;    
      case 2:
      WRITE(GET_DIR_PIN(3),true);
      break;    
      case 3:
      WRITE(GET_DIR_PIN(4),true);
      break;    
      case 4:
      WRITE(GET_DIR_PIN(5),true);
      break;    
      case 5:
      WRITE(GET_DIR_PIN(6),true);
      break;    
    }
  }else {
    switch(motorNumber){
      case 0:
      WRITE(GET_DIR_PIN(1),false);
      break;    
      case 1:
      WRITE(GET_DIR_PIN(2),false);
      break;    
      case 2:
      WRITE(GET_DIR_PIN(3),false);
      break;    
      case 3:
      WRITE(GET_DIR_PIN(4),false);
      break;    
      case 4:
      WRITE(GET_DIR_PIN(5),false);
      break;    
      case 5:
      WRITE(GET_DIR_PIN(6),false);
      break;    
    }
  }
}

void HAL::doSendPulse(int motorNumber){
  switch(motorNumber){
    case 0:
    WRITE(GET_STEP_PIN(1),true);
    _DELAY_1_9_US;
    WRITE(GET_STEP_PIN(1),false);
    _DELAY_1_9_US;
    break;    
    case 1:
    WRITE(GET_STEP_PIN(2),true);
    _DELAY_1_9_US;
    WRITE(GET_STEP_PIN(2),false);
    _DELAY_1_9_US;
    break;    
    case 2:
    WRITE(GET_STEP_PIN(3),true);
    _DELAY_1_9_US;
    WRITE(GET_STEP_PIN(3),false);
    _DELAY_1_9_US;
    break;    
    case 3:
    WRITE(GET_STEP_PIN(4),true);
    _DELAY_1_9_US;
    WRITE(GET_STEP_PIN(4),false);
    _DELAY_1_9_US;
    break;    
    case 4:
    WRITE(GET_STEP_PIN(5),true);
    _DELAY_1_9_US;
    WRITE(GET_STEP_PIN(5),false);
    _DELAY_1_9_US;
    break;    
    case 5:
    WRITE(GET_STEP_PIN(6),true);
    _DELAY_1_9_US;
    WRITE(GET_STEP_PIN(6),false);
    _DELAY_1_9_US;
    break;    
  }
}

void HAL::setupStepperMotor(){
      pinMode(GET_DIR_PIN(1),OUTPUT);
      pinMode(GET_STEP_PIN(1),OUTPUT);
      pinMode(GET_ENABLE_PIN(1),OUTPUT);
      digitalWrite(GET_ENABLE_PIN(1),LOW);

      pinMode(GET_DIR_PIN(2),OUTPUT);
      pinMode(GET_STEP_PIN(2),OUTPUT);
      pinMode(GET_ENABLE_PIN(2),OUTPUT);
      digitalWrite(GET_ENABLE_PIN(2),LOW);

      pinMode(GET_DIR_PIN(3),OUTPUT);
      pinMode(GET_STEP_PIN(3),OUTPUT);
      pinMode(GET_ENABLE_PIN(3),OUTPUT);
      digitalWrite(GET_ENABLE_PIN(3),LOW);

      pinMode(GET_DIR_PIN(4),OUTPUT);
      pinMode(GET_STEP_PIN(4),OUTPUT);
      pinMode(GET_ENABLE_PIN(4),OUTPUT);
      digitalWrite(GET_ENABLE_PIN(4),LOW);

      pinMode(GET_DIR_PIN(5),OUTPUT);
      pinMode(GET_STEP_PIN(5),OUTPUT);
      pinMode(GET_ENABLE_PIN(5),OUTPUT);
      digitalWrite(GET_ENABLE_PIN(5),LOW);

      pinMode(GET_DIR_PIN(6),OUTPUT);
      pinMode(GET_STEP_PIN(6),OUTPUT);
      pinMode(GET_ENABLE_PIN(6),OUTPUT);
      digitalWrite(GET_ENABLE_PIN(6),LOW);
}

//main loop
void TC7_Handler()
{
  TC_GetStatus(TC2, 1);
  Preference *state = Preference::getInstance();
  for(int i=0;i<6;i++){
      int _dest = state->motor[i].dest;
      int _cur = state->motor[i].cur;
      if(_cur <_dest){
          HAL::doSendDirection(i,CW);
          HAL::doSendPulse(i);
          state->motor[i].cur += STEP_RESOLUTION;
      }else if(_cur > _dest){
          HAL::doSendDirection(i,CCW);
          HAL::doSendPulse(i);
          state->motor[i].cur -= STEP_RESOLUTION;
      }
  }
  // TC_SetRC(TC2, 1, 656250);//1sec//debug
  // TC_SetRC(TC2, 1, 6563);
  // TC_SetRC(TC2, 1, 656);//0.001sec: 1000Hz
  TC_SetRC(TC2, 1, 65);//0.001sec: 1000Hz
}

