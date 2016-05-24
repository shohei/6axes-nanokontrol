#include <Arduino.h>
#include <String.h>
#include <ArduinoJson.h>
#include "Configuration.h"
#include "Preference.h"
#include "HAL.h"

void initState(){
  Preference *state = Preference::getInstance(); 
  for(int i=0;i<6;i++){
    state->motor[i].dest = 0;
    state->motor[i].cur = 0;
    state->readIndex[i] = 0;
    state->writeIndex[i] = 0;
    for(int j=0;j<BUF_NUM;j++){
      state->buffer[i][j]=0;
    }
    state->ringState[i] = RING_INIT;
  }
}

void setup()
{
  Serial.begin(115200);    // the GPRS baud rate
  // Serial.begin(9600);    // the GPRS baud rate
  while (!Serial) {
    // wait serial port initialization
  }
  Serial.println("Serial initialized.");
  delay(500);
  // pinMode(13,OUTPUT);//for debug
  initState();
  HAL::setupStepperMotor();
  HAL::setupTimer();
  HAL::startTimer();
}

void loop()
{
  String response;
  bool begin = false;
  bool end = false;

  while (!end) {
    if (Serial.available() > 0)
    {
      begin = true;
      response = Serial.readStringUntil('\n');
      // Serial.println(response);
      end = true;
    }
  }

  const char *charBuf = response.c_str();
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(charBuf);
  if (!root.success()) {
    // Serial.println("parseObject() failed");
    return;
  }

  const char* dump_command = root["dump"];
  if(!dump_command==NULL){
    dumpAll();
    return;
  }

  const char* jog_command = root["jog"];
  if(!jog_command==NULL){
    // Serial.println(jog_command);    
    int jog_command_number = atoi(jog_command);
    doJog(jog_command_number);
    // showStatus();
    return;
  }

  const char* dest1 = root["dest1"];
  const char* dest2 = root["dest2"];
  const char* dest3 = root["dest3"];
  const char* dest4 = root["dest4"];
  const char* dest5 = root["dest5"];
  const char* dest6 = root["dest6"];

  const char* dests[] = {dest1,dest2,dest3,dest4,dest5,dest6};

  Preference *state = Preference::getInstance(); 
  for(int i=0;i<6;i++){
    if(dests[i]!=NULL){
      // state->motor[i].dest = atoi(dests[i])*REQUIRED_PULSE;
      //check if writeIndex does not go one lap beyond readIndex
      if(state->ringState[i]==RING_INIT){
        state->buffer[i][state->writeIndex[i]] = atoi(dests[i])*REQUIRED_PULSE;
        state->writeIndex[i] = state->writeIndex[i] + 1;
        state->ringState[i] = WR_LEAD;
      } else if( state->ringState[i]==WR_LEAD&&(state->writeIndex[i] > state->readIndex[i])
          || (state->ringState[i]==RD_LEAD&&(state->writeIndex[i] < state->readIndex[i]))) {
        state->buffer[i][state->writeIndex[i]] = atoi(dests[i])*REQUIRED_PULSE;
        if(state->writeIndex[i]+1 > BUF_NUM){
          state->writeIndex[i] = 0;
          state->ringState[i] = RD_LEAD;
        }else {
          state->writeIndex[i] = state->writeIndex[i] + 1;
        }
      }
    }
  }
  //dump destination when received command
  // showStatus();
}

void dumpAll(){
  Preference *state = Preference::getInstance();
  for(int i=0;i<6;i++){
    Serial.print("destination");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(state->motor[i].dest);
    Serial.print(", current pos: ");
    Serial.println(state->motor[i].cur);
    for(int j=0;j<BUF_NUM;j++){
      Serial.print("buffer");
      Serial.print("[");
      Serial.print(i);
      Serial.print("]");
      Serial.print("[");
      Serial.print(j);
      Serial.print("]");
      Serial.println(state->buffer[i][j]);
    }
    Serial.print("ringState ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(state->ringState[i]);
    Serial.print("writeIndex ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(state->writeIndex[i]);
    Serial.print("readIndex ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(state->readIndex[i]);
  }
}

//  void showStatus(){
//   Preference *state = Preference::getInstance();
//   for(int i=0;i<6;i++){
//     Serial.print("destination");
//     Serial.print(i);
//     Serial.print(": ");
//     Serial.print(state->motor[i].dest);
//     Serial.print(", current pos: ");
//     Serial.println(state->motor[i].cur);
//   }
// }

void updateRingBufferIndex(Preference* state, int i, bool direction){
  if(state->ringState[i]==RING_INIT){
    if(direction==CW){
      state->buffer[i][state->writeIndex[i]] += JOG_WIDTH;
    }else if(direction==CCW){
      state->buffer[i][state->writeIndex[i]] -= JOG_WIDTH;
    }
    state->writeIndex[i] = state->writeIndex[i] + 1;
    state->ringState[i] = WR_LEAD;
  } else if(state->ringState[i]==WR_LEAD&&(state->writeIndex[i] > state->readIndex[i]) 
      || (state->ringState[i]==RD_LEAD&&(state->writeIndex[i] < state->readIndex[i]))) {
    if(direction==CW){
      state->buffer[i][state->writeIndex[i]] += JOG_WIDTH;
    }else if(direction==CCW){
      state->buffer[i][state->writeIndex[i]] -= JOG_WIDTH;
    }
    if(state->writeIndex[i]+1 > BUF_NUM){
      state->writeIndex[i] = 0;
      state->ringState[i] = RD_LEAD;
    }else {
      state->writeIndex[i] = state->writeIndex[i] + 1;
    }
  }
}


void doJog(int jog_command_number){
  Preference *state = Preference::getInstance();
  switch(jog_command_number){

    case UP1:
      Serial.println("UP1");
      updateRingBufferIndex(state,0,CW);
      break;

    case DOWN1:
      Serial.println("DOWN1");
      updateRingBufferIndex(state,0,CCW);
      break;

    case UP2:
      Serial.println("UP2");
      updateRingBufferIndex(state,1,CW);
      break;

    case DOWN2:
      Serial.println("DOWN2");
      updateRingBufferIndex(state,1,CCW);
      break;

    case UP3:
      Serial.println("UP3");
      updateRingBufferIndex(state,2,CW);
      break;

    case DOWN3:
      Serial.println("DOWN3");
      updateRingBufferIndex(state,2,CCW);
      break;

    case UP4:
      Serial.println("UP4");
      updateRingBufferIndex(state,3,CW);
      break;

    case DOWN4:
      Serial.println("DOWN4");
      updateRingBufferIndex(state,3,CCW);
      break;

    case UP5:
      Serial.println("UP5");
      updateRingBufferIndex(state,4,CW);
      break;

    case DOWN5:
      Serial.println("DOWN5");
      updateRingBufferIndex(state,4,CCW);
      break;

    case UP6:
      Serial.println("UP6");
      updateRingBufferIndex(state,5,CW);
      break;

    case DOWN6:
      Serial.println("DOWN6");
      updateRingBufferIndex(state,5,CCW);
      break;
  }
}
