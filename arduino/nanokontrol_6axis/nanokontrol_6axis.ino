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
  }
}

void setup()
{
  Serial.begin(115200);    // the GPRS baud rate
  while (!Serial) {
    // wait serial port initialization
  }
  Serial.println("Serial initialized.");
  delay(500);
  pinMode(13,OUTPUT);//for debug
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
    Serial.println("parseObject() failed");
    return;
  }

  const char* jog_command = root["jog"];
  if(!jog_command==NULL){
    Serial.println(jog_command);    
    int jog_command_number = atoi(jog_command);
    doJog(jog_command_number);
    showStatus();
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
      state->motor[i].dest = atoi(dests[i]) * LENGTH_MAGNIFIER;
    }
  }
   //dump destination when received command
   showStatus();
 }

 void showStatus(){
  Preference *state = Preference::getInstance();
  for(int i=0;i<6;i++){
    Serial.print("destination");
    Serial.print(i);
    Serial.print(": ");
    Serial.print(state->motor[i].dest);
    Serial.print(", current pos: ");
    Serial.println(state->motor[i].cur);
  }
}

void doJog(int jog_command_number){
  Preference *state = Preference::getInstance();
  switch(jog_command_number){

    case UP1:
    Serial.println("UP1");
    state->motor[0].dest += JOG_WIDTH;
    break;

    case DOWN1:
    Serial.println("DOWN1");
    state->motor[0].dest -= JOG_WIDTH;
    break;

    case UP2:
    Serial.println("UP2");
    state->motor[1].dest += JOG_WIDTH;
    break;

    case DOWN2:
    Serial.println("DOWN2");
    state->motor[1].dest -= JOG_WIDTH;
    break;

    case UP3:
    Serial.println("UP3");
    state->motor[2].dest += JOG_WIDTH;
    break;

    case DOWN3:
    Serial.println("DOWN3");
    state->motor[2].dest -= JOG_WIDTH;
    break;

    case UP4:
    Serial.println("UP4");
    state->motor[3].dest += JOG_WIDTH;
    break;

    case DOWN4:
    Serial.println("DOWN4");
    state->motor[3].dest -= JOG_WIDTH;
    break;

    case UP5:
    Serial.println("UP5");
    state->motor[4].dest += JOG_WIDTH;
    break;

    case DOWN5:
    Serial.println("DOWN5");
    state->motor[4].dest -= JOG_WIDTH;
    break;

    case UP6:
    Serial.println("UP6");
    state->motor[5].dest += JOG_WIDTH;
    break;

    case DOWN6:
    Serial.println("DOWN6");
    state->motor[5].dest -= JOG_WIDTH;
    break;
  }
}
