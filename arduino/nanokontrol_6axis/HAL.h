#ifndef _HAL_H
#define _HAL_H

#include <stdint.h>

#define F_CPU       21000000        // should be factor of F_CPU_TRUE
#define F_CPU_TRUE  84000000        // actual CPU clock frequency

class HAL{
public:
    HAL();
    virtual ~HAL();
    static void setupTimer();
    static void startTimer();
};



#endif