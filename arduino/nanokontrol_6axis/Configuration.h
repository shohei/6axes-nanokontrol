#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

#define JOG_CW -1000
#define JOG_CCW 1000

#define LENGTH_MAGNIFIER 100L
#define JOG_WIDTH 100

// #define GAIN 10

////////////////////////////////////////////////
//MOTOR PIN SETTINGS

//X
#define M1_STEP       200
#define M1_DIR_PIN    62
#define M1_STEP_PIN   63
#define M1_ENABLE_PIN 48

//Y->XX
#define M2_STEP       200
#define M2_DIR_PIN    64
#define M2_STEP_PIN   65
#define M2_ENABLE_PIN 46

//Z->Y
#define M3_STEP       200
#define M3_DIR_PIN    66
#define M3_STEP_PIN   67
#define M3_ENABLE_PIN 44

//E0->YY
#define M4_STEP       200
#define M4_DIR_PIN    28 
#define M4_STEP_PIN   36 
#define M4_ENABLE_PIN 42

//E1->Z
#define M5_STEP       200
#define M5_DIR_PIN    41 
#define M5_STEP_PIN   43 
#define M5_ENABLE_PIN 39 

//E2->ZZ
#define M6_STEP       200
#define M6_DIR_PIN    47 
#define M6_STEP_PIN   32 
#define M6_ENABLE_PIN 45 


enum JOG{ 
	UP1 = 1,
	DOWN1= 2,
	UP2 = 3,
	DOWN2 = 4,
	UP3 = 5,
	DOWN3= 6,
	UP4 = 7,
	DOWN4 = 8,
	UP5 = 9,
	DOWN5 = 10,
	UP6 = 11,
	DOWN6 = 12
};


#endif