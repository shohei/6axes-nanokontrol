#ifndef _PREFERENCE_H
#define _PREFERENCE_H

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
};

#endif