#include "../hardware/bluetooth.h"
#include "../hardware/run.h"
#include "../hardware/lamp.h"

#define TX_MAX_NUMBER    25

volatile uint8_t i=0;
uint8_t outputBuf[TX_MAX_NUMBER];
static uint8_t bleBuf[8];
//volatile uint8_t BleAssignedName[]={"AT+SPPNAME=ForenScope CSI"};
//volatile uint8_t BleAssignedBaud[]={"AT+BAUD=1"}; //setup baud rate is 9600


void BlueTooth_Init(void)
{
   BLE_RST_RC4_SetHigh() ; //BLE is high
   BLE_MODE_RC2_SetLow();
   
}


void BlueTooth_SetupAT_Function(void)
{
     static uint8_t i,j,n,m,times;
	 static uint8_t seq=1;
	 
	 n= sizeof(BleAssignedName)/sizeof(BleAssignedName[0]);
	 m= sizeof(BleAssignedBaud)/sizeof(BleAssignedBaud[0]);

	 switch(seq){
		 
	 case 0:
	      
         return ;
         
	 break;
	
	 case 1 :
          BLE_MODE_RC2_SetLow();
         
          if(run_t.bleSetName==0){
			//for(i=0;i<n;i++){
              seq=1;
			EUSART_Write(BleAssignedName[i]);
             i++; 
            if(i==(n-1)){
                run_t.bleSetName=1;
              
            }
          }
          else{ 
              seq=2;
              DELAY_milliseconds(200);
          }
          
	     
		
		
	 break;
	 
	 case 2:
         BLE_MODE_RC2_SetLow();
		if(run_t.bleSetBaud==0){
            seq=2;
		   EUSART_Write(BleAssignedBaud[j]);
                j++;
				if(j==(m-1)){
                    run_t.bleSetBaud=1;
                    
				}
			}
        else{
            seq=3;
            DELAY_milliseconds(200);
        }
          
        
		
		
	 break;
	 
	 case 3:
         if(run_t.bleSetName==1 && run_t.bleSetBaud==1){
             times++;
              seq=1;
              i=0;
              j=0;
              run_t.bleSetName=0;
               run_t.bleSetBaud=0;
             if(times==30){
             seq =0;
             run_t.bleSetName=1;
              run_t.bleSetBaud=1;
             EUSART_Initialize_9600();
             BLE_MODE_RC2_SetHigh();
             }
         }
         else{
           seq =1;
         }
		
	  break;
     }
	 
}
/*****************************************************************************
 * 
 *Function Name: void BlueTooth_CheckLink(void)
 *Function: check blue tooth if link for phone
 *Input Ref:NO
 *Return Ref:NO
 * 
 *****************************************************************************/
uint8_t BlueTooth_CheckLink(void)
{
	if(BLE_LINK_RC5_GetValue() ==0){ //blue tooth has link
		
		return 1;
		
	}
	else{
		
		return 0; //blie don't link for phone
	}
	
	
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

void Ble_RxData_EUSART(void)
{
	PIE3bits.RC1IE = 0;
        
        
      bleBuf[i]=RC1REG;
        PIE3bits.TX1IE = 0;
		if(i==0){
			
			
	        if(bleBuf[0]=='M'){
	             TX1REG = bleBuf[0];//recdata[i]; // ???????? // ??
                 
			}
			else i=0;
		}
		else if(i==1){
            
	        if(bleBuf[1]=='X')
	             TX1REG = bleBuf[1];//recdata[i]; // ???????? // ??
	        else i=0;
		}
		else if(i==2){
            

			if(bleBuf[2]=='B' || bleBuf[2]=='L' || bleBuf[2]=='F' ){
                ble_t.bleInputCmd[0]=bleBuf[2];
	             TX1REG = bleBuf[2];//recdata[i]; // ???????? // ??
            }
			else i=0;
		}
		else if(i==3){

		    if((bleBuf[3] -0x30) >12){
                 i=0;
            }
			else{
			   ble_t.bleInputCmd[1]=bleBuf[3]; 
              
			   TX1REG = bleBuf[3];//recdata[i]; // ???????? // ??
			}

		 }
        i++;
		if(i==4){
            i=0;
            run_t.gBle_Mode=1;
        }
        
     PIE3bits.RC1IE = 1; 
     PIE3bits.TX1IE = 1;
	
	
}

/*********************************************************************
	*
	*Function Name:void Bluetooth_RunCmd(void)
	*Funciton :key input value of response active
	*Input Ref: input key pressed of value .
	*Return Ref: NO
	*
*********************************************************************/
void Bluetooth_RunCmd(void)
{

    static unsigned char tcolor32,tcolor8,tlaser,flag,bleTarget;
	static uint8_t color32=0xff,color8=0xff,laser=0xff;
	uint8_t cmdType=ble_t.bleInputCmd[0];
     bleTarget=ble_t.bleInputCmd[1]-0x30;
	//bleIndex=bleInputCmd[2]-0x30;
	//static uint8_t keyBR_Counts=0;
	if(ble_t.bleInputCmd[0] =='B' )
	{
		flag =1;
	    run_t.gBleItem=1;
    }
	else if(ble_t.bleInputCmd[0]=='L'){
		
		flag =2;
		 run_t.gBleItem=1;
	}
	else if(ble_t.bleInputCmd[0]=='F'){
		
		flag=3;
		 run_t.gBleItem=1;
	}
	else{
		flag =0;
		run_t.gBleItem=0;
	}
	 

	if(flag==1){ //LED AND LASER
		
		switch(bleTarget){
			
	   
		case 1:	            
	
				 run_t.gLampWhite_32=1;
                    run_t.gTurnOffLamp=1;
                    run_t.gRunOrder= white_32;
                    run_t.gID_flag = white_32;
		
							
		break;
	case 2:
			    
	
		 run_t.gLampWhite_8=1;
                     run_t.gTurnOffLamp=1;
                     run_t.gRunOrder= white_8;
                     run_t.gID_flag = white_8;
		
		  
       
	break;
	
	case 3:
		   Laser_ON();
		    run_t.gTurnOffLamp=1;
            run_t.gRunOrder= laser;
             run_t.gID_flag = laser;
	break;
	default:
	break;

	}
	}
    if(flag ==2)
	{
	    if(bleTarget == 0){
			
			//ADJ_LampBrightnessADD();
			 run_t.gRunOrder= brightness_add;
			
		}
		if(bleTarget == 1){
			
			//ADJ_LampBrightnessSUB();
			run_t.gRunOrder= brightness_sub;
			
		}
	
	}
	
	if(flag==3){
		
			 run_t.gTurnOffLamp=0;
                    run_t.gRunOrder= turnOffLamp;
                    run_t.gADJ_brightness=0;
	}
	
}

/******************************************************************************
 * 
 *Function Name: EUSART_TxData(uint8_t index) 
 * Function:transmit data
 * Input Ref:
 * Return Ref:
 * 
 *****************************************************************************/
void EUSART_BleCommandTxData(uint8_t index)
{
    
   //AT+SPPNAME=ForenScope CSI
    
     outputBuf[0]='A';
     outputBuf[1]='T';
     outputBuf[2]='+';
     outputBuf[3]='S';
     outputBuf[4]='P';
     outputBuf[5]='P';
     outputBuf[6]='N';
     outputBuf[7]='A';
     outputBuf[8]='M';
     outputBuf[9]='E';
     outputBuf[10]='=';
       
	outputBuf[11]='F'; //0x46
	outputBuf[12]='o'; //0x50
    outputBuf[13]='r'; //0x4F ->order
    outputBuf[14]='e';
	outputBuf[15]='n'; 
    outputBuf[16]='S';
    outputBuf[17]='c';
    outputBuf[18]='o';
    outputBuf[19]='p';
    outputBuf[20]='e';
    outputBuf[21]=' ';
    outputBuf[22]='C';
    outputBuf[23]='S';
    outputBuf[24]='I';
//	outputBuf[3]=index+0x30;	// change to ascii number for decimal number 0~9
   if(run_t.eusartTx_flag ==0){
   	   PIE3bits.TXIE=0;
      if(transOngoingFlag==0){
            TX1REG = outputBuf[run_t.eusartTx_Num];
	        run_t.eusartTx_Num++;
            
       }
	   transOngoingFlag=1;
	   if(run_t.eusartTx_Num==25)run_t.eusartTx_flag=1;
	    PIE3bits.TXIE=1;
   	}
   
}