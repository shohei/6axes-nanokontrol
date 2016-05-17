#ifndef _NANOKONTROL_6AXIS_H
#define _NANOKONTROL_6AXIS_H

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
	virtual ~Preference(){};	
	static Preference* pref;
public:	
	static Preference* getInstance(void){
		return pref;
	};
	Motor motor[6];
};


Preference *Preference::pref = new Preference();

#endif