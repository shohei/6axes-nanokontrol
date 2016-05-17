#include <Arduino.h>
#include <String.h>
#include <ArduinoJson.h>
#include "Configuration.h"
#include "Preference.h"
#include "HAL.h"

void setupStepperPin(Preference* pref, int motorNumber, int step, int dirPin, int stepPin, int enablePin){
  pref->motor[motorNumber-1].dirPin = dirPin;
  pref->motor[motorNumber-1].stepPin = stepPin;
  pref->motor[motorNumber-1].enablePin = enablePin;
  pinMode(enablePin,OUTPUT);
  digitalWrite(enablePin,LOW);
}

void setupSteppers(){
  Preference *pref = Preference::getInstance();
  setupStepperPin(pref,1,200,62,63,48);//X
  setupStepperPin(pref,2,200,64,65,46);//Y->XX
  setupStepperPin(pref,3,200,66,67,44);//Z->Y
  setupStepperPin(pref,4,200,28,36,42);//E0->YY
  setupStepperPin(pref,5,200,41,43,39);//E1->Z
  setupStepperPin(pref,6,200,47,32,45);//E2->ZZ
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
  setupSteppers();
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

  const char* dest1 = root["dest1"];
  const char* dest2 = root["dest2"];
  const char* dest3 = root["dest3"];
  const char* dest4 = root["dest4"];
  const char* dest5 = root["dest5"];
  const char* dest6 = root["dest6"];

  const char* dests[] = {dest1,dest2,dest3,dest4,dest5,dest6};

  Preference *state = Preference::getInstance(); 
  for(int i=0;i<6;i++){
    state->motor[i].dest = atoi(dests[i]);
  }
   //dump destination when received command
   showDestination();
 }

 void showDestination(){
  Preference *state = Preference::getInstance();
  for(int i=0;i<6;i++){
    Serial.print("destination");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(state->motor[i].dest);
  }
}
