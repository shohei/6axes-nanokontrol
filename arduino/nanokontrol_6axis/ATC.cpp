#include "ATC.h"
#include "Preference.h"
#include "Configuration.h"
#include "HAL.h"

void ATC::doSendDirection(bool isClockWise){
  if(isClockWise){
    WRITE(ATC_DIR_PIN,ATC_CW);
  }else {
    WRITE(ATC_DIR_PIN,ATC_CCW);
  }
}

void ATC::doSendPulse(){
    WRITE(ATC_STEP_PIN,true);
    _DELAY_1_9_US;
    WRITE(ATC_STEP_PIN,false);
    _DELAY_1_9_US;
}

void ATC::turnCW(){
	Preference *state = Preference::getInstance();
	state->wheel.dest = ATC_JOG;
}

void ATC::turnCCW(){
	Preference *state = Preference::getInstance();
	state->wheel.dest = -ATC_JOG;
}
