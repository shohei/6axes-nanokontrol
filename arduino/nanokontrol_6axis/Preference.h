#ifndef _PREFERENCE_H
#define _PREFERENCE_H

#include "Configuration.h"

typedef struct {
	long dest;
	long cur;
} Motor;

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
	float buffer[6][BUF_NUM];
	int readIndex[6];
	int writeIndex[6];
	int ringState;
};

#endif