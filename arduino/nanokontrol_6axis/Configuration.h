#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

////////////////////////////////////////////////
//MOTOR AND SLIDER SETTINTS 
//PROTOTYPE 0
// #define SLIDER_PITCH 12
//POTOTYPE 1
#define SLIDER_PITCH 6 
#define MICROSTEP 32
#define PULSE_PER_REVOLUTION 200
#define REQUIRED_PULSE (MICROSTEP*PULSE_PER_REVOLUTION/SLIDER_PITCH)
// PROTOTYPE0
// #define JOG_DISTANCE 10 
//PROTOTYPE1
#define JOG_DISTANCE 5
#define JOG_WIDTH (JOG_DISTANCE*REQUIRED_PULSE)
#define STEP_RESOLUTION 1
#define CW  true
#define CCW false
#define ANY false
#define ZLENGTH 250
#define INITIALZ 100 

////////////////////////////////////////////////
//RING BUFFER
// #define BUF_NUM  4 
// #define BUF_NUM  64 
// #define BUF_NUM  128 
#define BUF_NUM 1024
#define RING_INIT 0
#define WR_LEAD 1
#define RD_LEAD 2


////////////////////////////////////////////////
//ENDSTOP SETTINGS
#define ES_FREE 1
#define ES_HIT 0
#define Z_OFFSET_HOMING 5

////////////////////////////////////////////////
//MOTOR PIN SETTINGS

//X
#define M1_STEP       200
#define M1_DIR_PIN    62
#define M1_STEP_PIN   63
#define M1_ENABLE_PIN 48
//XMIN
#define M1_MIN_PIN 22

//E2->XX
#define M2_STEP       200
#define M2_DIR_PIN    47 
#define M2_STEP_PIN   32 
#define M2_ENABLE_PIN 45 
//XMAX
#define M2_MIN_PIN 30 

//E0->Y
#define M3_STEP       200
#define M3_DIR_PIN    28 
#define M3_STEP_PIN   36 
#define M3_ENABLE_PIN 42
//YMIN
#define M3_MIN_PIN 24 

//E1->YY
#define M4_STEP       200
#define M4_DIR_PIN    41 
#define M4_STEP_PIN   43 
#define M4_ENABLE_PIN 39 
//YMAX
#define M4_MIN_PIN 38 

//Y->Z
#define M5_STEP       200
#define M5_DIR_PIN    64
#define M5_STEP_PIN   65
#define M5_ENABLE_PIN 46
//ZMIN
#define M5_MIN_PIN 26

//Z->ZZ
#define M6_STEP       200
#define M6_DIR_PIN    66
#define M6_STEP_PIN   67
#define M6_ENABLE_PIN 44
//ZMAX
#define M6_MIN_PIN 34 

enum JOG_COMMAND{ 
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

enum JOG_OR_SLIDER{
	SLIDER,JOG	
};


#endif