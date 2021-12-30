/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F24K40
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"
#include "hardware/key.h"
#include "hardware/run.h"
#include "hardware/bluetooth.h"

uint8_t BleOrder[]={"AT"};
uint8_t BleReset[]={"AT+RESET"};
/*
                         Main application
 */
void main(void)
{
    static uint8_t i,j,n,m;
     uint8_t  KeyValue;
    // Initialize the device
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:
      BlueTooth_Init();
    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
     FAN_OFF();
  
    while (1)
    {
        
        
        if(run_t.eusartTx_flag<2){
            BLE_MODE_RC2_SetLow();
            EUSART_BleCommandTxData_Name(0);
            if(run_t.eusartTx_flag==1){
                n++;
             run_t.eusartTx_Num=0;
             run_t.eusartTx_flag=0;
             DELAY_milliseconds(200);
             if(n>10){
               run_t.eusartTx_flag=3;
              
             }
            }
        }
        if( run_t.eusartTx_flag==3){
              BLE_MODE_RC2_SetHigh();
          EUSART_SetRxInterruptHandler(Ble_RxData_EUSART);
          
        Bluetooth_RunCmd();
      
         CheckRun();
         FAN_Run();
              
              
        }
#if 0
        if(ble_t.ble_reset_flag <2){
           EUSART_BleCommandTxReset();
           if(ble_t.ble_reset_flag==1){
               i++;
               ble_t.ble_reset_flag=0;
               ble_t.ble_reset_n=0;
               if(i>15){
                 ble_t.ble_reset_flag++;
                 ble_t.ble_reset_flag=1;
               }
                }
           }
#endif
     
 #if 0
        if(ble_t.ble_openbaud_flag <2){
            if(ble_t.ble_openbaud_flag ==1){
             EUSART_BleCommandTxOpenSetBaud();
             j++;
             ble_t.ble_openbaud_flag=0;
             ble_t.ble_openbaud_n=0;
             if(j>10){
                 ble_t.ble_openbaud_flag=3;
               ble_t.ble_openbaud_flag=1;
             }
            }
        }
        else  if(run_t.eusartTx_Baud_flag<2){
            EUSART_BleCommandTxBaud();
           if(run_t.eusartTx_Baud_flag==1){
                m++;
             run_t.eusartTx_Baud_n=0;
             run_t.eusartTx_Baud_flag=0;
             DELAY_milliseconds(200);
             if(m>10){
                run_t.eusartTx_Baud_flag=2;
                 run_t.eusartTx_Baud_flag=1;
               // run_t.eusartTx_flag++;
              //  EUSART_Initialize_9600();
             }
            }
        }
        else{
        
        
         if(run_t.eusartTx_Baud_flag==2){
            EUSART_BleCommandTxData_Name(0);
            if(run_t.eusartTx_flag==1){
                n++;
             run_t.eusartTx_Num=0;
             run_t.eusartTx_flag=0;
             DELAY_milliseconds(200);
             if(n>10){
               run_t.eusartTx_flag++;
               run_t.eusartTx_flag=1;
               run_t.eusartTx_Baud_flag=3;
             }
            }
        }
        }
        
        

       
#endif
     //   EUSART_SetRxInterruptHandler(Ble_RxData_EUSART);
      ///     Bluetooth_RunCmd();
      //    CheckRun();
      //   FAN_Run();
#if 0
        n= sizeof(BleReset)/sizeof(BleReset[0]);
        for(i=0;i<n;i++){
          EUSART_Write(BleReset[i]);
        }
        //if(i>=n)i=0;
        
        for(j=0;j<2;j++){
            EUSART_Write(BleOrder[j]);
        }
        if(j>=2)j=0;
        DELAY_milliseconds(200);
#endif
#if 0
       if(run_t.bleSetName==0){
			//for(i=0;i<n;i++){
             // seq=1;
			EUSART_Write(BleAssignedName[i]);
             i++; 
            if(i==(n-1)){
                run_t.bleSetName=1;
              
            }
          }
          else{ 
              m++;
              run_t.bleSetName=0;
              i=0;
              DELAY_milliseconds(200);
              if(m==50){
                 run_t.bleSetName=1;
              }
              
          }
#endif
      // BlueTooth_SetupAT_Function();
#if 0
        n= sizeof(BleAssignedName)/sizeof(BleAssignedName[0]);
	     m= sizeof(BleAssignedBaud)/sizeof(BleAssignedBaud[0]);

	
	
	
          BLE_MODE_RC2_SetLow();
         
          if(run_t.bleSetName==0){
        
			EUSART_Write(BleAssignedName[i]);
             i++; 
            if(i==(n-1)){
                run_t.bleSetName=1;
               
						//DELAY_milliseconds(100);
			}
          }
          else{
             run_t.bleSetName=0;
             i=0;
            DELAY_milliseconds(500);
          }
#endif   
#if 0
        run_t.bleLinked = BlueTooth_CheckLink();
        if(run_t.bleLinked==1){
            if(link==0){
                EUSART_Initialize_9600();
                link++;
            }
        BLE_MODE_RC2_SetLow();
        BlueTooth_SetupAT_Function();
        }
        KeyValue = KEY_Scan();
         EUSART_SetRxInterruptHandler(Ble_RxData_EUSART);
          if(KeyValue !=0){
            CheckMode(KeyValue);
          }
          else if(run_t.gBle_Mode==1){
           
           // BlueTooth_SetupAT_Function();
            run_t.bleLinked = BlueTooth_CheckLink();
           // if(run_t.bleLinked==1){
               // EUSART_SetRxInterruptHandler(Ble_RxData_EUSART);
               // Bluetooth_RunCmd();
           // }
            Bluetooth_RunCmd();
            run_t.gBle_Mode=0;
          } 
         CheckRun();
         FAN_Run();
#endif
}
}

/**
 End of File
*/