#include "HAL.h"
#include "Arduino.h"
#include "Preference.h"
#include "Configuration.h"
#include "fastio.h"

//increment current position

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

#define SET_INPUT(pin) pmc_enable_periph_clk(g_APinDescription[pin].ulPeripheralId); \
PIO_Configure(g_APinDescription[pin].pPort, PIO_INPUT, g_APinDescription[pin].ulPin, 0)
#define SET_OUTPUT(pin) PIO_Configure(g_APinDescription[pin].pPort, PIO_OUTPUT_1, \
g_APinDescription[pin].ulPin, g_APinDescription[pin].ulPinConfiguration)


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
  WRITE(GET_ENABLE_PIN(1),false);

  pinMode(GET_DIR_PIN(2),OUTPUT);
  pinMode(GET_STEP_PIN(2),OUTPUT);
  pinMode(GET_ENABLE_PIN(2),OUTPUT);
      // SET_OUTPUT(GET_ENABLE_PIN(2));
  WRITE(GET_ENABLE_PIN(2),false);

  pinMode(GET_DIR_PIN(3),OUTPUT);
  pinMode(GET_STEP_PIN(3),OUTPUT);
  pinMode(GET_ENABLE_PIN(3),OUTPUT);
  WRITE(GET_ENABLE_PIN(3),false);

  pinMode(GET_DIR_PIN(4),OUTPUT);
  pinMode(GET_STEP_PIN(4),OUTPUT);
  pinMode(GET_ENABLE_PIN(4),OUTPUT);
  WRITE(GET_ENABLE_PIN(4),false);

  pinMode(GET_DIR_PIN(5),OUTPUT);
  pinMode(GET_STEP_PIN(5),OUTPUT);
  pinMode(GET_ENABLE_PIN(5),OUTPUT);
  WRITE(GET_ENABLE_PIN(5),false);

  pinMode(GET_DIR_PIN(6),OUTPUT);
  pinMode(GET_STEP_PIN(6),OUTPUT);
  pinMode(GET_ENABLE_PIN(6),OUTPUT);
  WRITE(GET_ENABLE_PIN(6),false);
}


void HAL::homing(){
  while(!XMIN || !XXMIN || !YMIN || !YYMIN || !ZMIN || !ZZMIN){
    if(!XMIN){
      HAL::doSendDirection(0,CCW);
      HAL::doSendPulse(0);
    }
    if(!XXMIN){
      HAL::doSendDirection(1,CCW);
      HAL::doSendPulse(1);
    }
    if(!YMIN){
      HAL::doSendDirection(2,CCW);
      HAL::doSendPulse(2);
    }
    if(!YYMIN){
      HAL::doSendDirection(3,CCW);
      HAL::doSendPulse(3);
    }
    if(!ZMIN){
      HAL::doSendDirection(4,CCW);
      HAL::doSendPulse(4);
    }
    if(!ZZMIN){
      HAL::doSendDirection(5,CCW);
      HAL::doSendPulse(5);
    }
  }
};


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
    }else if(_cur == _dest){
      //update readIndex (but only once!)
      //check if readIndex is behind writeIndex
      if((state->ringState[i]==WR_LEAD)&&(state->readIndex[i] < state->writeIndex[i])
        || (state->ringState[i]==RD_LEAD)&&(state->readIndex[i] > (state->writeIndex[i]))){
          //update dest
        state->motor[i].dest = state->buffer[i][state->readIndex[i]];
        if(state->readIndex[i]+1 > BUF_NUM-1) {
          state->readIndex[i] = 0;
          state->ringState[i] = WR_LEAD;
        } else {
          state->readIndex[i] = state->readIndex[i] + 1;
        }
      } 
    }
  }
  // TC_SetRC(TC2, 1, 656250);//1sec//debug
  // TC_SetRC(TC2, 1, 6563);
  // TC_SetRC(TC2, 1, 656);//0.001sec: 1000Hz
  TC_SetRC(TC2, 1, 65);//0.001sec: 1000Hz
}

