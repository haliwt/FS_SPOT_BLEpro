#include "run.h"
#include "key.h"
#include "lamp.h"

#define NORMAL_LEVEL_DEFAULT	10
#define NORMAL_LEVEL_MAX		20
#define NORMAL_LEVEL_MIN		10
#define NORMAL_LEVEL_STEP		2
#define NORMAL_LEVEL_PWM_STEP	8
#define NORMAL_LEVEL_PWM_MAX	159 //


static uint16_t level;

static void ADJ_LampBrightnessADD(void);
static void ADJ_LampBrightnessSUB(void);
static void setColorWhite_32(uint16_t val);	// green brightness'
static void FAN_ON(void);
static void FAN_OFF(void);
/***************************************************************************
	*
	*Function Name:void CheckMode(uint8_t value)
	*Function: The first input LED ON,the second input key LED OFF
	*Input Ref:key be pressed of value
	*Return Ref:NO
	*
****************************************************************************/
 void CheckMode(uint8_t keyValue)
 {
 
    static uint8_t  inputKey_power,inputKey_lamp_32,inputKey_lamp_8,inputKey_laser,inputKey_add,inputKey_sub;

	switch(keyValue){
       case 0:

	     if(!keyValue)
		  	return ;
		break;
	   case 0x1: //power On
	  
	       
           inputKey_power = inputKey_power ^ 0x01;
	        if(inputKey_power ==1){
	            run_t.gPowerOn =1;
	            run_t.gRunOrder= powerON;
	            inputKey_lamp_8=0;
	            inputKey_lamp_32=0;
                inputKey_laser=0;
                
	        }
	        else{
	             
	           run_t.gPowerOn =0;
               run_t.gRunOrder= noLamp;
              
               
	       }
            
			    
	  break;
   
	   case 0x02: //white 32
           if(run_t.gPowerOn==1){
                inputKey_lamp_32 = inputKey_lamp_32 ^ 0x01;
                if(inputKey_lamp_32 ==1){
                    run_t.gLampWhite_32=1;
                    run_t.gCloseLamp=0;
                    run_t.gRunOrder= white_32;
                     inputKey_lamp_8=0;
                     inputKey_laser=0;
                     
	        
                }
                else{
                    run_t.gCloseLamp=1;
                    run_t.gRunOrder= noLamp;
                }
              
           }
           else{
               
               
            }
       
		
			 
	  break;
   
	   case 0x04://white 8
           
	          if(run_t.gPowerOn==1){
                 inputKey_lamp_8 =  inputKey_lamp_8 ^ 0x01;
                if( inputKey_lamp_8 ==1){
                    run_t.gLampWhite_8=1;
                     run_t.gCloseLamp=0;
                     run_t.gRunOrder= white_8;
                     inputKey_lamp_32=0;
                      inputKey_laser=0;
                     
	                
                }
                else{
                    run_t.gCloseLamp=1;
                     run_t.gRunOrder= noLamp;
                }
             }
           else{
               
               
               
           }
			
   
	   break;
   
	   case 0x08://laser 
		    if(run_t.gPowerOn==1){
                inputKey_laser = inputKey_laser ^ 0x01;
                if(inputKey_laser ==1){
                     run_t.gCloseLamp=0;
                     run_t.gRunOrder= laser;
                     inputKey_lamp_32=0;
                     inputKey_lamp_8=0;
                     
	                
                }
                else{
                    run_t.gCloseLamp=1;
                    run_t.gRunOrder= noLamp;
                }
              
           }
           else{
               
               
               
           }
	  break;
   
   
	   case 0x10: //sub  "-"
         if(run_t.gPowerOn==1){
             
            run_t.gRunOrder= brightness_add;
           
	        
	     }
	   break;
   
	   case 0x20: //add
	    
        if(run_t.gPowerOn==1){
             
            run_t.gRunOrder= brightness_sub;
            
	     }
   
	   break;
	   
   
	   default:
   
   		break;
 
    }
 }
 /***************************************************************************
	*
	*Function Name:void CheckRun(void)
	*Function: Run order
	*Input Ref:NO
	*Return Ref:NO
	*
****************************************************************************/  
 void CheckRun(void)
 {
     
     switch(run_t.gRunOrder){
           
         case noLamp:
             
             ALL_LED_OFF();
             run_t.gPowerOn=0;
             run_t.gADJ_brightness=0;
             run_t.gTim0_30s=1;
             if(run_t.gTimer_flag==1)
                 run_t.gFAN_flag=0;//FAN_ON_FUN();
             
             break;
             
        case powerON:
           run_t.gPowerOn=1;
           WhichOneLed_ON(1);
           
        break;
         case white_32:
             LED1_Power_ON();
             WhichOneLed_ON(2);
             ColorWhite_32_ON();
            run_t.gColorPwm=79; //50
            PWM3_LoadDutyValue(run_t.gColorPwm);

             WhichOneColorLamp_ON(1);
             run_t.gADJ_brightness = 0x01; //color white 32 
              __delay_ms(100); 
             run_t.gFAN_flag=1;//FAN_ON_FUN();
              run_t.gTim0_30s=0;//timer 30s flag;
             break;
         case white_8:
              LED1_Power_ON();
              WhichOneLed_ON(3);
              ColorWhite_8_ON();
             run_t.gColorPwm=79; //50
              PWM3_LoadDutyValue(run_t.gColorPwm);
              WhichOneColorLamp_ON(2);
              run_t.gADJ_brightness = 0x02; //color white 8
               __delay_ms(100); 
              run_t.gFAN_flag=1;//FAN_ON_FUN();
              run_t.gTim0_30s=0;//timer 30s flag;
              run_t.gTimer_flag=0;
             break;
         case laser :
             LED1_Power_ON();
             WhichOneLed_ON(4);
             Laser_ON();
              __delay_ms(100); 
             run_t.gFAN_flag=1;//FAN_ON_FUN();
             run_t.gTim0_30s=0;//timer 30s flag;
             run_t.gTimer_flag=0;
             break;
             
         case brightness_add:
              run_t.gFAN_flag=0;//FAN_OFF_FUN();
              LED1_Power_ON();
              WhichOneLed_ON(5);
              ADJ_LampBrightnessADD();
                __delay_ms(100); 
             run_t.gFAN_flag=1;//FAN_ON_FUN();
             run_t.gTim0_30s=0;//timer 30s flag;
             run_t.gTimer_flag=0;
             break;
         case brightness_sub:
              run_t.gFAN_flag=0;//FAN_OFF_FUN();
             LED1_Power_ON();
             WhichOneLed_ON(6);
              ADJ_LampBrightnessSUB();
                __delay_ms(100); 
             run_t.gFAN_flag=1;//FAN_ON_FUN();
             run_t.gTim0_30s=0;//timer 30s flag;
             run_t.gTimer_flag=0;
             
             break;
         default:
             break;
             
             
             
     
     }
 
 }
 
 /**************************************************************
	*
	*Function Name:static void ADJ_LampBrightnessADD(void)
	*Function: 
	*Input Ref:NO
	*Return Ref:NO
	*
**************************************************************/
static void ADJ_LampBrightnessADD(void)
{
	
	  switch( run_t.gADJ_brightness ){

	     case 0x01://Color -white 32 

                ColorWhite_8_OFF();
               
            level+=NORMAL_LEVEL_STEP; //2
			if(level>NORMAL_LEVEL_MAX) level=NORMAL_LEVEL_MAX; //20
                 
             setColorWhite_32(level);	// green brightness
              ColorWhite_32_ON();
               __delay_ms(100); 
             run_t.gFAN_flag=1;//FAN_ON_FUN();
             
	     break;

		 case 0x02: //Color white 8
		 		 ColorWhite_32_OFF();
               
            level+=NORMAL_LEVEL_STEP; //2
			if(level>NORMAL_LEVEL_MAX) level=NORMAL_LEVEL_MAX; //20
                 
             setColorWhite_32(level);	// green brightness
             ColorWhite_8_ON();
                __delay_ms(100); 
             run_t.gFAN_flag=1;//FAN_ON_FUN();

		 break;

		

		 default:

		 break;


	  }


}

static void ADJ_LampBrightnessSUB(void)
{
     switch(run_t.gADJ_brightness ){

	     case 0x01://Color -white 32 
             ColorWhite_8_OFF();
             if(level<NORMAL_LEVEL_MIN+NORMAL_LEVEL_STEP)	level=NORMAL_LEVEL_MIN;//10
			 else 	level-=NORMAL_LEVEL_STEP;
           
             setColorWhite_32(level);	// green brightness
             ColorWhite_32_ON();
             __delay_ms(100); 
             run_t.gFAN_flag=1;//FAN_ON_FUN();
           break;
           
         case 0x02:
              ColorWhite_32_OFF();
             if(level<NORMAL_LEVEL_MIN+NORMAL_LEVEL_STEP)	level=NORMAL_LEVEL_MIN;//10
			 else 	level-=NORMAL_LEVEL_STEP;
           
             setColorWhite_32(level);	// green brightness
             ColorWhite_8_ON();
              __delay_ms(100); 
             run_t.gFAN_flag=1;//FAN_ON_FUN();
             
             break;
         default :
             break;

     }
}

static void setColorWhite_32(uint16_t val)	// green brightness
{
	uint16_t pwmValue;

	if(val>NORMAL_LEVEL_MAX) val=NORMAL_LEVEL_MAX;
	pwmValue=(val)*NORMAL_LEVEL_PWM_STEP -1; //20*8=160

	if(pwmValue>NORMAL_LEVEL_PWM_MAX) pwmValue=NORMAL_LEVEL_PWM_MAX;
	PWM3_LoadDutyValue(pwmValue);
}

void FAN_Run(void)
{
    if(run_t.gFAN_flag==1){
       void FAN_ON();
    }
    else {
    FAN_OFF();
    
    }

}

static void FAN_ON(void)
{
  FAN_RC3_SetLow();
}
static void FAN_OFF(void)
{
  FAN_RC3_SetHigh();
}