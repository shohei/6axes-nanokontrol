#include "Printer.h"
#include "Preference.h"
#include "Configuration.h"
#include "HAL.h"

void Printer::initState(){
  Preference *state = Preference::getInstance(); 
  for(int i=0;i<6;i++){
    state->motor[i].dest = 0;
    state->motor[i].cur = 0;
    // state->endstop[i].status = ES_FREE;
    state->readIndex[i] = 0;
    state->writeIndex[i] = 0;
    for(int j=0;j<BUF_NUM;j++){
      state->buffer[i][j]=0;
    }
    state->ringState[i] = RING_INIT;
  }
}

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
    for(int j=0;j<BUF_NUM;j++){
      //clear all buffer
      state->buffer[i][j]=0;
    }
    state->motor[i].dest = -ZLENGTH * REQUIRED_PULSE;
  }
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


void Printer::doJog(int jog_command_number){
  Preference *state = Preference::getInstance();
  const char* dummy[] = {"dummy"};
  switch(jog_command_number){
    case UP1:
      Serial.println("UP1");
      Printer::updateRingBufferIndex(state,0,JOG,CW,dummy);
      break;

    case DOWN1:
      Serial.println("DOWN1");
      Printer::updateRingBufferIndex(state,0,JOG,CCW,dummy);
      break;

    case UP2:
      Serial.println("UP2");
      Printer::updateRingBufferIndex(state,1,JOG,CW,dummy);
      break;

    case DOWN2:
      Serial.println("DOWN2");
      Printer::updateRingBufferIndex(state,1,JOG,CCW,dummy);
      break;

    case UP3:
      Serial.println("UP3");
      Printer::updateRingBufferIndex(state,2,JOG,CW,dummy);
      break;

    case DOWN3:
      Serial.println("DOWN3");
      Printer::updateRingBufferIndex(state,2,JOG,CCW,dummy);
      break;

    case UP4:
      Serial.println("UP4");
      Printer::updateRingBufferIndex(state,3,JOG,CW,dummy);
      break;

    case DOWN4:
      Serial.println("DOWN4");
      Printer::updateRingBufferIndex(state,3,JOG,CCW,dummy);
      break;

    case UP5:
      Serial.println("UP5");
      Printer::updateRingBufferIndex(state,4,JOG,CW,dummy);
      break;

    case DOWN5:
      Serial.println("DOWN5");
      Printer::updateRingBufferIndex(state,4,JOG,CCW,dummy);
      break;

    case UP6:
      Serial.println("UP6");
      Printer::updateRingBufferIndex(state,5,JOG,CW,dummy);
      break;

    case DOWN6:
      Serial.println("DOWN6");
      Printer::updateRingBufferIndex(state,5,JOG,CCW,dummy);
      break;
  }
}

void Printer::updateRingBufferIndex(Preference* state, int i, int jog_or_slider, bool direction, const char* dests[]){
  if(state->ringState[i]==RING_INIT){
    switch(jog_or_slider){
      case SLIDER:
        state->buffer[i][0] = atoi(dests[i])*REQUIRED_PULSE;
        break;
      case JOG:
        switch(direction){
          case CW:
            state->buffer[i][0] = +JOG_WIDTH;
            break;
          case CCW:
            state->buffer[i][0] = -JOG_WIDTH;
            break;
        }  
        break;
    }
    state->writeIndex[i] = 1;
    state->motor[i].dest = state->buffer[i][0];
    state->ringState[i] = WR_LEAD;
  } else if(state->ringState[i]==WR_LEAD&&(state->writeIndex[i] >= state->readIndex[i]) 
      || (state->ringState[i]==RD_LEAD&&(state->writeIndex[i] < state->readIndex[i]))) {
    switch(jog_or_slider){
      case SLIDER:
        state->buffer[i][state->writeIndex[i]] = atoi(dests[i])*REQUIRED_PULSE;
        break;
      case JOG:
        switch(direction){
          case CW:
            if(!state->writeIndex[i]==0){
              state->buffer[i][state->writeIndex[i]] = state->buffer[i][state->writeIndex[i]-1] + JOG_WIDTH;
            } else {
              state->buffer[i][0] = state->buffer[i][BUF_NUM-1] + JOG_WIDTH;
            }
            break;
          case CCW:
            if(!state->writeIndex[i]==0){
              state->buffer[i][state->writeIndex[i]] = state->buffer[i][state->writeIndex[i]-1] - JOG_WIDTH;
            } else {
              state->buffer[i][0] = state->buffer[i][BUF_NUM-1] - JOG_WIDTH;
            }
            break;
        }
        break;
    }
    state->writeIndex[i]++;
    if(state->writeIndex[i] > BUF_NUM-1){
      state->writeIndex[i] = 0;
      state->ringState[i] = RD_LEAD;
    }
  }
}

