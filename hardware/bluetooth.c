#include "bluetooth.h"
#include "run.h"
#include "lamp.h"
volatile uint8_t i=0;

static uint8_t bleBuf[8];
volatile uint8_t BleAssignedName[]={"AT+SPPNAME=ForenScope CSI"};

//volatile uint8_t BleSetOpenBaud[]={"AT+BAUDABT=1"}; //allow set baud rate 
volatile uint8_t BleAssignedBaud[]={"AT+BAUD=1"}; //setup baudrate is 9600
uint8_t outputBuf[8];

void BlueTooth_Init(void)
{
   BLE_RST_RC4_SetHigh() ; //BLE is high
   BLE_MODE_RC2_SetHigh();  //setup transfer
   
}


void BlueTooth_SetupAT_Function(void)
{
     static uint8_t i,j,n;
	 static uint8_t seq=1;
	 
	if(run_t.bleLinked==0)
	{
	  BLE_MODE_RC2_SetHigh();
	}
	else
	   BLE_MODE_RC2_SetLow();
	   
	   
	if(run_t.bleSetName==0){
			for(n=0;n<27;n++){
			EUSART_Write(BleAssignedName[n]);
				
					if(BleAssignedName[n]=='\0'){
						n=50;
						run_t.bleSetName=1;
						DELAY_milliseconds(100);
					}
			}
	}
	run_t.bleSetName=0;
	   
	 
	 switch(seq){
		 
	 case 0:
	   
	       return ;
	 break;
	
	 case 10 :
		if(run_t.bleOpenBaud==0){
			for(i=0;i<15;i++){
			EUSART_Write(BleSetOpenBaud[i]);
					
					if(BleSetOpenBaud[i]=='\0'){
						run_t.bleOpenBaud=1;
						DELAY_milliseconds(100);
					}
			}
		}
		seq=2;
	 break;
	 
	 case 20:
		if(run_t.bleSetBaud==0){
			for(j=0;j<12;j++){
				EUSART_Write(BleAssignedBaud[j]);
					if(BleAssignedBaud[j]=='\0'){
				
						run_t.bleSetBaud=1;
						DELAY_milliseconds(100);
					}
			}
		}
		seq=3;
	 break;
	 
	 case 3:
		if(run_t.bleSetName==0){
			for(n=0;n<27;n++){
			EUSART_Write(BleAssignedName[n]);
				
					if(BleAssignedName[n]=='\0'){
						
						run_t.bleSetName=1;
						DELAY_milliseconds(100);
					}
			}
		}
		
		if(run_t.bleLinked==1){
		       seq =1;
			    run_t.bleOpenBaud=0;
        run_t.bleSetBaud=0;
        run_t.bleSetName=0;
        }
        else{
            seq=1;
        run_t.bleOpenBaud=0;
        run_t.bleSetBaud=0;
        run_t.bleSetName=0;
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
		if(i==4)i=0;
        
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
	    
    }
	else if(ble_t.bleInputCmd[0]=='L'){
		
		flag =2;
		
	}
	else if(ble_t.bleInputCmd[0]=='F'){
		
		flag=3;
		
	}
	else flag =0;
	 

	if(flag==1){
		
		switch(bleTarget){
			
	   
		case 1:	            
				ColorWhite_8_OFF();
				ColorWhite_32_ON();
				run_t.gADJ_brightness=1;
				 __delay_ms(1); 
             run_t.gFAN_flag=1;//FAN_ON_FUN();
              run_t.gTim0_30s=0;//timer 30s flag;
             run_t.gTimer_flag=0;
							
		break;
	case 2:
			    
		ColorWhite_32_OFF();
		ColorWhite_8_ON();
		run_t.gADJ_brightness=2;
		 __delay_ms(1); 
        run_t.gFAN_flag=1;//FAN_ON_FUN();
        run_t.gTim0_30s=0;//timer 30s flag;
        run_t.gTimer_flag=0;
	break;
	
	case 3:
		Laser_ON();
		 __delay_ms(1); 
        run_t.gFAN_flag=1;//FAN_ON_FUN();
        run_t.gTim0_30s=0;//timer 30s flag;
        run_t.gTimer_flag=0;
		
	break;
	default:
	break;

	}
	}
    if(flag ==2)
	{
	    if(bleTarget == 0){
			
			ADJ_LampBrightnessADD();
			
		}
		if(bleTarget == 1){
			
			ADJ_LampBrightnessSUB();
			
		}
	
	}
	
	if(flag==3){
		
		ColorWhite_32_OFF();
		ColorWhite_8_OFF();
		Laser_OFF();
	    run_t.gADJ_brightness=0;
             run_t.gTim0_30s=1;
             if(run_t.gTimer_flag==1)
              run_t.gFAN_flag=0;//FAN_ON_FUN();
	}
	
		               
			

             
			
	
	
}