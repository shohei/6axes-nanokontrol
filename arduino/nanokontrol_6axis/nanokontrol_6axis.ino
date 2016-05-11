#include <Arduino.h>
#include <String.h>
#include <ArduinoJson.h>
#include "DRV8825.h"
#include "position.h"
#include "Command.h"
#include "Configuration.h"

DRV8825 stepper1(200, 62, 63);//X
DRV8825 stepper2(200, 28, 36);//XX
DRV8825 stepper3(200, 64, 65);//Y
DRV8825 stepper4(200, 41, 43);//YY
DRV8825 stepper5(200, 66, 67);//Z
DRV8825 stepper6(200, 47, 32);//ZZ
int enablePins[] = {48,46,44,42,39,45};

void enableAllStepper(){
  for(int i=0;i<6;i++){
    pinMode(enablePins[i],OUTPUT);
    digitalWrite(enablePins[i],LOW);
    Serial.print("stepper");
    Serial.print(i+1);
    Serial.println(" enabled");
  }
}

void setupSteppers(){
  enableAllStepper();
  stepper1.setRPM(300);
  stepper2.setRPM(300);
  stepper3.setRPM(300);
  stepper4.setRPM(300);
  stepper5.setRPM(300);
  stepper6.setRPM(300);
  stepper1.setMicrostep(32);
  stepper2.setMicrostep(32);
  stepper3.setMicrostep(32);
  stepper4.setMicrostep(32);
  stepper5.setMicrostep(32);
  stepper6.setMicrostep(32);
}

void setup()
{
  Serial.begin(115200);    // the GPRS baud rate
  while (!Serial) {
    // wait serial port initialization
  }
  Serial.println("Serial initialized.");
  delay(500);
  setupSteppers();
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
     int jog_command_number = atoi(jog_command);
     doJog(jog_command_number);
     return;
   }
   const char* dest1 = root["dest1"];
   const char* dest2 = root["dest2"];
   const char* dest3 = root["dest3"];
   const char* dest4 = root["dest4"];
   const char* dest5 = root["dest5"];
   const char* dest6 = root["dest6"];

   Position *pos = Position::getInstance();
   pos->cur1 = pos->dest1;
   pos->cur2 = pos->dest2;
   pos->cur3 = pos->dest3;
   pos->cur4 = pos->dest4;
   pos->cur5 = pos->dest5;
   pos->cur6 = pos->dest6;
   pos->dest1 = atoi(dest1);
   pos->dest2 = atoi(dest2);
   pos->dest3 = atoi(dest3);
   pos->dest4 = atoi(dest4);
   pos->dest5 = atoi(dest5);
   pos->dest6 = atoi(dest6);

   // debugPrint();

   relativeMove();
 }

// void moveStepper1(int dest){
//   difference = dest - current;
// }

void debugPrint(){
  Position *pos = Position::getInstance();
  Serial.println("current position: ");
  Serial.println(pos->cur1);
  Serial.println(pos->cur2);
  Serial.println(pos->cur3);
  Serial.println(pos->cur4);
  Serial.println(pos->cur5);
  Serial.println(pos->cur6);
  Serial.println("destination: ");
  Serial.println(pos->dest1);
  Serial.println(pos->dest2);
  Serial.println(pos->dest3);
  Serial.println(pos->dest4);
  Serial.println(pos->dest5);
  Serial.println(pos->dest6);
}

void relativeMove(){
  //TODO: distance = dest - cur;
  //distance * coeff = rotationDegree;
  Position *pos = Position::getInstance();
  int dist1 = GAIN*(pos->dest1 - pos->cur1);
  int dist2 = GAIN*(pos->dest2 - pos->cur2);
  int dist3 = GAIN*(pos->dest3 - pos->cur3);
  int dist4 = GAIN*(pos->dest4 - pos->cur4);
  int dist5 = GAIN*(pos->dest5 - pos->cur5);
  int dist6 = GAIN*(pos->dest6 - pos->cur6);


  Serial.println("dist1: ");
  Serial.println(dist1);
  Serial.println("dist2: ");
  Serial.println(dist2);
  Serial.println("dist3: ");
  Serial.println(dist3);
  Serial.println("dist4: ");
  Serial.println(dist4);
  Serial.println("dist5: ");
  Serial.println(dist5);
  Serial.println("dist6: ");
  Serial.println(dist6);

  // TODO: should use interrupt, or timer.
  // This DRV8825 library seems to lock whole process.
  // stepper1.rotate(dist1);
  // stepper2.rotate(dist2);
  // stepper3.rotate(dist3);
  // stepper4.rotate(dist4);
  // stepper5.rotate(dist5);
  // stepper6.rotate(dist6);
}

void doJog(int jog_command_number){
 switch(jog_command_number){

  case UP1:
  Serial.println("UP1");
  stepper1.rotate(JOG_CW);
  break;

  case DOWN1:
  Serial.println("DOWN1");
  stepper1.rotate(JOG_CCW);
  break;

  case UP2:
  Serial.println("UP2");
  stepper2.rotate(JOG_CW);
  break;

  case DOWN2:
  Serial.println("DOWN2");
  stepper2.rotate(JOG_CCW);
  break;

  case UP3:
  Serial.println("UP3");
  stepper3.rotate(JOG_CW);
  break;

  case DOWN3:
  Serial.println("DOWN3");
  stepper3.rotate(JOG_CCW);
  break;

  case UP4:
  Serial.println("UP4");
  stepper4.rotate(JOG_CCW);
  break;

  case DOWN4:
  Serial.println("DOWN4");
  stepper4.rotate(JOG_CCW);
  break;

  case UP5:
  Serial.println("UP5");
  stepper5.rotate(JOG_CW);
  break;

  case DOWN5:
  Serial.println("DOWN5");
  stepper5.rotate(JOG_CCW);
  break;

  case UP6:
  Serial.println("UP6");
  stepper6.rotate(JOG_CW);
  break;

  case DOWN6:
  Serial.println("DOWN6");
  stepper6.rotate(JOG_CCW);
  break;
}
}