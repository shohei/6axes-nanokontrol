#ifndef _PREFERENCE_H
#define _PREFERENCE_H

typedef struct {
	int step;
	int dirPin;
	int stepPin;
	int enablePin;
	int dest;
	int cur;
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
};

#endif