#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

////////////////////////////////////////////////
//MOTOR AND SLIDER SETTINTS 
#define SLIDER_PITCH 12
#define MICROSTEP 32
#define PULSE_PER_REVOLUTION 200
#define REQUIRED_PULSE (MICROSTEP*PULSE_PER_REVOLUTION/SLIDER_PITCH)
#define JOG_DISTANCE 10
#define JOG_WIDTH (JOG_DISTANCE*REQUIRED_PULSE)
#define STEP_RESOLUTION 1
#define CW  false
#define CCW true
#define ZLENGTH 600

////////////////////////////////////////////////
//RING BUFFER
#define BUF_NUM  4 
// #define BUF_NUM  64 
// #define BUF_NUM  128 
// #define BUF_NUM 1024
#define RING_INIT 0
#define WR_LEAD 1
#define RD_LEAD 2

////////////////////////////////////////////////
//ENDSTOP PIN SETTINGS
#define M1_MIN_PIN 22
#define M2_MIN_PIN 23
#define M3_MIN_PIN 24 
#define M4_MIN_PIN 25 
#define M5_MIN_PIN 26
#define M6_MIN_PIN 27 

////////////////////////////////////////////////
//ENDSTOP SETTINGS
#define ES_FREE false
#define ES_HIT true
#define Z_OFFSET_HOMING 5

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