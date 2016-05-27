#include <Arduino.h>
#include "Communication.h"
#include "Preference.h"

void Com::dumpAll(){
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

void Com::showStatus(){
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

