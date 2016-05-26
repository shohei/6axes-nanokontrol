#include "Printer.h"
#include "Preference.h"
#include "Configuration.h"
#include "HAL.h"

void Printer::setOrigin(int motorNumber){
	Preference *state = Preference::getInstance();
	state->motor[motorNumber].cur = 0;
	state->motor[motorNumber].dest = 0;
}

void Printer::setOffsetToDestination(int motorNumber){
	Preference *state = Preference::getInstance();
	state->motor[motorNumber].dest = Z_OFFSET_HOMING * REQUIRED_PULSE;
}


void Printer::checkEndstop(int motorNumber){
	Preference *state = Preference::getInstance();
	switch(motorNumber){
		case 0:
			state->endstop[motorNumber].status = READ(GET_MIN_PIN(1));
		break;
		case 1:
			state->endstop[motorNumber].status = READ(GET_MIN_PIN(2));
		break;
		case 2:
			state->endstop[motorNumber].status = READ(GET_MIN_PIN(3));
		break;
		case 3:
			state->endstop[motorNumber].status = READ(GET_MIN_PIN(4));
		break;
		case 4:
			state->endstop[motorNumber].status = READ(GET_MIN_PIN(5));
		break;
		case 5:
			state->endstop[motorNumber].status = READ(GET_MIN_PIN(6));
		break;
	}
}

//TODO: refer repetier-firmware
void Printer::homing(){
  Preference *state = Preference::getInstance();
  for(int i=0;i<6;i++){
    state->motor[i].dest = -ZLENGTH * REQUIRED_PULSE;
  }
  // while(!M1_PIN|| !XXMIN || !YMIN || !YYMIN || !ZMIN || !ZZMIN){
  //   if(!XMIN){
  //     HAL::doSendDirection(0,CCW);
  //     HAL::doSendPulse(0);
  //   }
  //   if(!XXMIN){
  //     HAL::doSendDirection(1,CCW);
  //     HAL::doSendPulse(1);
  //   }
  //   if(!YMIN){
  //     HAL::doSendDirection(2,CCW);
  //     HAL::doSendPulse(2);
  //   }
  //   if(!YYMIN){
  //     HAL::doSendDirection(3,CCW);
  //     HAL::doSendPulse(3);
  //   }
  //   if(!ZMIN){
  //     HAL::doSendDirection(4,CCW);
  //     HAL::doSendPulse(4);
  //   }
  //   if(!ZZMIN){
  //     HAL::doSendDirection(5,CCW);
  //     HAL::doSendPulse(5);
  //   }
  // }
}

void Printer::setupStepperMotor(){
  pinMode(GET_DIR_PIN(1),OUTPUT);
  pinMode(GET_STEP_PIN(1),OUTPUT);
  pinMode(GET_ENABLE_PIN(1),OUTPUT);
  WRITE(GET_ENABLE_PIN(1),false);

  pinMode(GET_DIR_PIN(2),OUTPUT);
  pinMode(GET_STEP_PIN(2),OUTPUT);
  pinMode(GET_ENABLE_PIN(2),OUTPUT);
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
