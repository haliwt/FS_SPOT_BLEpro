#ifndef __RUN_H_
#define __RUN_H_
#include "key.h"

typedef struct{

    
    uint8_t gRunOrder;
    uint8_t gPowerOn;
    uint8_t gLampWhite_32;
    uint8_t gLampWhite_8;
    uint8_t gTurnOffLamp;
    uint8_t gID_flag;
    uint8_t gADJ_brightness;
    uint8_t gFAN_flag;
    uint8_t gTim0_30s;
    uint8_t gTimer_flag;
    uint8_t eusartTx_flag;
    uint8_t eusartTx_Num;
    uint8_t bleOpenBaud;
    uint8_t bleSetBaud;
    uint8_t bleSetName;
    uint8_t bleLinked;
    
    uint16_t gColorPwm;
 
}RUNREF_T;
RUNREF_T run_t;

typedef enum Color{noLamp,turnOffLamp,white_32,white_8,laser,brightness_add,brightness_sub,powerON};

 void CheckMode(uint8_t keyValue);
 void CheckRun(void);
 void FAN_Run(void);
 void FAN_OFF(void);



#endif 