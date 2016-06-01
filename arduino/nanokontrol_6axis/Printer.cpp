#include "Printer.h"
#include "Preference.h"
#include "Configuration.h"
#include "HAL.h"

void Printer::standby(){ 
  Serial.println("printer standing by");
  Preference *state = Preference::getInstance();
  for(int i=0;i<6;i++){
    for(int j=0;j<BUF_NUM;j++){
      //clear all buffer
      state->buffer[i][j]=0;
    }
    state->writeIndex[i]=0;
    state->readIndex[i]=0;
    state->ringState[i]=RING_INIT;  
    state->motor[i].dest = INITIALZ * REQUIRED_PULSE;
  }
}

void Printer::toggleMode(){
  Preference *state = Preference::getInstance(); 
  state->manualMode ^= true; //toggle boolean
  if(state->manualMode){
    Serial.println("set to manual mode");
  } else {
    Serial.println("set to auto mode");
  }
}


void Printer::initState(){
  Preference *state = Preference::getInstance(); 
  for(int i=0;i<6;i++){
    state->motor[i].dest = 0;
    state->motor[i].cur = 0;
    state->wheel.dest = 0;
    state->wheel.cur = 0;
    state->readIndex[i] = 0;
    state->writeIndex[i] = 0;
    state->isHomed[i] = false;
    for(int j=0;j<BUF_NUM;j++){
      state->buffer[i][j]=0;
    }
    state->ringState[i] = RING_INIT;
  }
  state->homing = false;
  state->manualMode = false;
}

void Printer::checkEndstop(int motorNumber){
  Preference *state = Preference::getInstance();
  int s;
  if(state->homing){
    switch(motorNumber){
      case 0:
        if(state->isHomed[0]==false&&READ(GET_MIN_PIN(1))==ES_HIT){
          Serial.println("ES1 HIT!");
          state->isHomed[0]=true;
          state->motor[0].dest = 0;
          state->motor[0].cur = 0;
        }
        break;
      case 1:
        if(state->isHomed[1]==false&&READ(GET_MIN_PIN(2))==ES_HIT){
          Serial.println("ES2 HIT!");
          state->isHomed[1]=true;
          state->motor[1].dest = 0;
          state->motor[1].cur = 0;
        } 
        break;
      case 2:
        if(state->isHomed[2]==false&&READ(GET_MIN_PIN(3))==ES_HIT){
          Serial.println("ES3 HIT!");
          state->isHomed[2]=true;
          state->motor[2].dest = 0;
          state->motor[2].cur = 0;
        } 
        break;
      case 3:
        if(state->isHomed[3]==false&&READ(GET_MIN_PIN(4))==ES_HIT) {
          Serial.println("ES4 HIT!");
          state->isHomed[3]=true;
          state->motor[3].dest = 0;
          state->motor[3].cur = 0;
        }
        break;
      case 4:
        if(state->isHomed[4]==false&&READ(GET_MIN_PIN(5))==ES_HIT) {
          Serial.println("ES5 HIT!");
          state->isHomed[4]=true;
          state->motor[4].dest = 0;
          state->motor[4].cur = 0;
        }
        break;
      case 5:
        if(state->isHomed[5]==false&&READ(GET_MIN_PIN(6))==ES_HIT) {
          Serial.println("ES6 HIT!");
          state->isHomed[5]=true;
          state->motor[5].dest = 0;
          state->motor[5].cur = 0;
        }
        break;
    }
  }
  if(state->isHomed[0]&&state->isHomed[1]&&state->isHomed[2]
    &&state->isHomed[3]&&state->isHomed[4]&&state->isHomed[5]){
    Serial.println("All axis homed.");
    for(int i=0;i<6;i++){
      state->isHomed[i] = false;
    }
    state->homing = false;
    Serial.print("move to initial height: ");
    Serial.println(INITIALZ);
    Printer::goToInitialZ(); 
  }
}

void Printer::goToInitialZ(){
  Preference *state = Preference::getInstance();
  const char* dest = String(INITIALZ).c_str(); 
  const char* dests[] = {dest,dest,dest,dest,dest,dest}; 
  for(int i=0;i<6;i++){
    Printer::updateRingBufferIndex(state,i,SLIDER,ANY,dests);
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
    state->writeIndex[i]=0;
    state->readIndex[i]=0;
    state->ringState[i]=RING_INIT;  
    state->motor[i].dest = -ZLENGTH * REQUIRED_PULSE;
  }
  state->homing = true;
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

  pinMode(ATC_STEP_PIN,OUTPUT);
  pinMode(ATC_DIR_PIN,OUTPUT);
  pinMode(ATC_ENABLE_PIN,OUTPUT);
}

void Printer::setupEndStop(){
  pinMode(M1_MIN_PIN,INPUT);
  pinMode(M2_MIN_PIN,INPUT);
  pinMode(M3_MIN_PIN,INPUT);
  pinMode(M4_MIN_PIN,INPUT);
  pinMode(M5_MIN_PIN,INPUT);
  pinMode(M6_MIN_PIN,INPUT);
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
        state->buffer[i][0] = atof(dests[i])*REQUIRED_PULSE;
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
        state->buffer[i][state->writeIndex[i]] = atof(dests[i])*REQUIRED_PULSE;
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

