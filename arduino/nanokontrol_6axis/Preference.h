#ifndef _PREFERENCE_H
#define _PREFERENCE_H

typedef struct {
	int step;
	int dirPin;
	int stepPin;
	int enablePin;
} Motor;

class Preference 
{
private:
	Preference(){};
	virtual ~Preference(){this->state=false;};	
	static Preference* pref;
public:	
	static Preference* getInstance(void){
		return pref;
	};
	Motor motor[6];
	int state;
};

#endif