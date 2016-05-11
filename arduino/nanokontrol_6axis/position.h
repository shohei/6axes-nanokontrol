#ifndef _POSITION_H
#define _POSITION_H
#include <String.h>

class Position
{
private:
	Position(void){};
	static Position* pos;
public:
	static Position* getInstance(void){
		return pos;
	};
	int dest1;
	int dest2;
	int dest3;
	int dest4;
	int dest5;
	int dest6;
	int cur1;
	int cur2;
	int cur3;
	int cur4;
	int cur5;
	int cur6;
};

Position *Position::pos = new Position();

#endif