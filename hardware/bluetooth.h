#ifndef __BLUETOOTH_H_
#define __BLUETOOTH_H_
#include "key.h"

const uint8_t BleAssignedName[]={"AT+SPPNAME=ForenScope CSI"};
const uint8_t BleAssignedBaud[]={"AT+BAUD=1"}; //setup baud rate is 9600
typedef struct _BLE{
    
    
    uint8_t bleInputCmd[8];
    uint8_t ble_reset_n;
    uint8_t ble_reset_flag;
    uint8_t ble_openbaud_n;
    uint8_t ble_openbaud_flag;
    uint8_t ble_response_n;
    uint8_t ble_response_flag;
    
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

void EUSART_BleCommandTxData_Name(uint8_t index);
void EUSART_BleCommandTxBaud(void);
void EUSART_BleCommandTxReset(void);
void EUSART_BleCommandTxOpenSetBaud(void);
void Ble_RxData_EUSART_ISR(void);

void EUSART_BleResponseEvent(void);

#endif