#ifndef _NANOKONTROL_6AXIS_H
#define _NANOKONTROL_6AXIS_H

class Preference {
public:	
	Preference();
	virtual ~Preference();	
	static *Preference pref;
	Preference* getInstance(){
		return pref;
	};
	Motor motor[6];
};

typedef struct {
	int step;
	int dirPin;
	int stepPin;
	int enablePin;
} Motor;

Preference* Preference::pref = new Preference();

#endif