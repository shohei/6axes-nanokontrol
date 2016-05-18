#include <Arduino.h>
#include <String.h>
#include <ArduinoJson.h>
#include "Configuration.h"
#include "Preference.h"
#include "HAL.h"

void setup()
{
  Serial.begin(115200);    // the GPRS baud rate
  while (!Serial) {
    // wait serial port initialization
  }
  Serial.println("Serial initialized.");
  delay(500);
  pinMode(13,OUTPUT);//for debug
  for(int i=0;i<6;i++){
    HAL::enableStepperMotor(i);
  }
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
