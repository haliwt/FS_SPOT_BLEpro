#ifndef __BLUETOOTH_H_
#define __BLUETOOTH_H_
#include "key.h"


typedef struct{
    
    uint8_t bleInputCmd[8];
    
}BLE_T;

BLE_T ble_t;

volatile uint8_t BleSetOpenBaud[]={"AT+BAUDABT=1"}; //allow set baud rate 
volatile uint8_t transOngoingFlag=0;
void BlueTooth_Init(void);
void BlueTooth_SetupAT_Function(void);
uint8_t  BlueTooth_CheckLink(void);
void Ble_RxData_EUSART(void);
void Bluetooth_RunCmd(void);

void Bluetooth_RunCmd(void);



#endif