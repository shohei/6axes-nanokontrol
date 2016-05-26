#ifndef _PREFERENCE_H
#define _PREFERENCE_H

#include "Configuration.h"

typedef struct {
	long dest;
	long cur;
} Motor;

typedef struct {
	bool status;
} Endstop;

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
	Endstop endstop[6];
	float buffer[6][BUF_NUM];
	int readIndex[6];
	int writeIndex[6];
	int ringState[6];
};

#endif