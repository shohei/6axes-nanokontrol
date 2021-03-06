#ifndef _PREFERENCE_H
#define _PREFERENCE_H

#include "Configuration.h"

typedef struct {
  long dest;
  long cur;
} Motor;

typedef struct {
  long dest;
  long cur;
} Wheel;

class Preference 
{
  private:
    Preference(){};
    virtual ~Preference(){};	
    static Preference* state;
  public:	
    static Preference* getInstance(void){
      return state;
    };
    Motor motor[6];
    Wheel wheel;
    float buffer[6][BUF_NUM];
    int readIndex[6];
    int writeIndex[6];
    int ringState[6];
    bool isHomed[6];
    bool homing;
    bool manualMode;
};

#endif
