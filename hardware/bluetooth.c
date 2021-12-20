#include "bluetooth.h"
#include "run.h"

volatile uint8_t BleAssignedName[]={"AT+SPPNAME=ForenScope CSI"};
volatile uint8_t BleAssignedBaud[]={"AT+BAUD=1"};
uint8_t outputBuf[8];

void BlueTooth_Init(void)
{
   BLE_RST_RC4_SetHigh() ; //BLE is high
   BLE_MODE_RC2_SetLow();  //setup transfer
   
}

void BlueTooth_SetupAT_Function(void)
{
    
    
    
}

/******************************************************************************
 * 
 *Function Name: EUSART_TxData(uint8_t index) 
 * 
 * 
 *****************************************************************************/
void EUSART_CommandTxData(uint8_t index)
{
   

	outputBuf[0]='F'; //0x46
	outputBuf[1]='P'; //0x50
    outputBuf[2]='O'; //0x4F ->order
	outputBuf[3]=index; 
//	outputBuf[3]=index+0x30;	// change to ascii number for decimal number 0~9
   if(run_t.eusartTx_flag ==0){
   	   PIE3bits.TXIE=0;
      if(transOngoingFlag==0){
            TX1REG = outputBuf[run_t.eusartTx_Num];
	        run_t.eusartTx_Num++;
            
       }
	   transOngoingFlag=1;
	   if(run_t.eusartTx_Num==4)run_t.eusartTx_flag=1;
	    PIE3bits.TXIE=1;
   	}
   
}