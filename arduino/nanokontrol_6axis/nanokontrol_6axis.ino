#include <Arduino.h>
#include <String.h>
#include <ArduinoJson.h>
#include "Configuration.h"
#include "Preference.h"
#include "HAL.h"
#include "Printer.h"
#include "Communication.h"
#include "ATC.h"


void setup(){

  Serial.begin(115200);    
  while (!Serial) {
    // wait serial port initialization
  }
  Serial.println("Serial initialized.");
  delay(500);
  Printer::setupStepperMotor();
  Printer::setupEndStop();

  Printer::initState();

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

  const char* home_command = root["home"];
  if(home_command!=NULL){
    Serial.println("home Z axis");
    Printer::homing();
    return;
  }

  const char* atc_command = root["atc"];
  if(atc_command!=NULL){
    const char* _cw = "\x43\x57\x0";
    const char* _ccw = "\x43\x43\x57\x0"; 
    if(strcmp(atc_command,_cw)==0){
        ATC::turnCW();
      } else if(strcmp(atc_command,_ccw)==0){
        ATC::turnCCW();
      }
    return;
  }

  const char* dump_command = root["dump"];
  if(dump_command!=NULL){
    Com::dumpAll();
    return;
  }

  const char* standby_command = root["standby"];
  if(standby_command!=NULL){
    Printer::standby();
    return;
  }

  const char* mode_command = root["mode"];
  if(mode_command!=NULL){
    Printer::toggleMode();
    return;
  }

  const char* jog_command = root["jog"];
  if(jog_command!=NULL){
    int jog_command_number = atoi(jog_command);
    Printer::doJog(jog_command_number);
    // Com::showStatus();
    return;
  }

  const char* dest1 = root["dest1"];
  const char* dest2 = root["dest2"];
  const char* dest3 = root["dest3"];
  const char* dest4 = root["dest4"];
  const char* dest5 = root["dest5"];
  const char* dest6 = root["dest6"];

  const char* nan_char = "\x4e\x61\x4e\x0";//"NaN"

  const char* dests[] = {dest1,dest2,dest3,dest4,dest5,dest6};

  //debug
  // Serial.println("float precision?");
  // for(int i=0;i<6;i++){
  //   Serial.println(dests[i]);
  // }
  //end of debug

  Preference *state = Preference::getInstance(); 
  for(int i=0;i<6;i++){
    if(dests[i]!=NULL&&strcmp(dests[i],nan_char)!=0){
      //check if writeIndex does not go one lap beyond readIndex
      Printer::updateRingBufferIndex(state,i,SLIDER,ANY,dests);
    }
  }
  //dump destination when received command
  // Com::showStatus();
}

