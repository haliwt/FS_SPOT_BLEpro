#include "lamp.h"
/***************************************************************
 * *
 *Function Name: void ColorWhite_32_ON(void)
 *Function: On LAMP white 32 pcs
 *Input Ref: NO
 *Return Ref: NO
 *
***************************************************************/
void ColorWhite_32_ON(void)
{
  WHITE_32_RA6_SetHigh() ; 
}
void ColorWhite_32_OFF(void)
{
    WHITE_32_RA6_SetLow();
}
void ColorWhite_8_ON(void)
{
    WHITE_8_RA7_SetHigh();
}
void ColorWhite_8_OFF(void)
{
    WHITE_8_RA7_SetLow();
}
void Laser_ON(void)
{
  PWM4_LoadDutyValue(79);
}
void Laser_OFF(void)
{
    PWM4_LoadDutyValue(0);
}

void WhichOneColorLamp_ON(uint8_t colorlamp)
{
    switch(colorlamp){
        
        case 1:
             ColorWhite_8_OFF();
             ColorWhite_32_ON();
        break;
        
        case 2:
            ColorWhite_8_ON();
            ColorWhite_32_OFF();
        break;
        
        default:
        break;
    }
    
    
    
}
/***************************************************************
 * *
 *Function Name:TurnOff_ALL_Lamp(void)
 *Function: 
 *Input Ref:NO
 *Return Ref:NO
 * 
***************************************************************/
void TurnOff_ALL_Lamp(void)
{
    ColorWhite_32_OFF();
    ColorWhite_8_OFF();
    Laser_OFF();

}
/***************************************************************
 * *
 *Function Name: void LED_1_ON(void)
 *Function: On LED ONE 
 *Input Ref: NO
 *Return Ref: NO
 *
***************************************************************/
void LED1_Power_ON(void)
{
    LED1_RA0_SetHigh();  
}
void LED1_Power_OFF(void)
{
    LED1_RA0_SetLow(); 
}

void LED_2_ON(void)
{
    LED2_RA1_SetHigh() ;
}
void LED_2_OFF(void)
{
    LED2_RA1_SetLow() ;
}

void LED_3_ON(void)
{
    LED3_RA2_SetHigh() ;
}
void LED_3_OFF(void)
{
    LED3_RA2_SetLow() ;
}

void LED_4_ON(void)
{
    LED4_RA3_SetHigh();
}
void LED_4_OFF(void)
{
    LED4_RA3_SetLow();
}

void LED_5_ON(void)
{
    LED5_RA4_SetHigh();
}
void LED_5_OFF(void)
{
    LED5_RA4_SetLow() ;
}

void LED_6_ON(void)
{
    LED6_RA5_SetHigh() ;
}
void LED_6_OFF(void)
{
    LED6_RA5_SetLow() ;
}

/***************************************************************
 * *
 *Function Name: void LED_1_ON(void)
 *Function: On LED ONE 
 *Input Ref: NO
 *Return Ref: NO
 *
***************************************************************/
void ALL_LED_OFF(void)
{
    LED1_RA0_SetLow(); 
    LED2_RA1_SetLow() ;
    LED3_RA2_SetLow() ;
    LED4_RA3_SetLow();
    LED5_RA4_SetLow() ;
    LED6_RA5_SetLow() ;
}
/***************************************************************
 * *
 *Function Name: void WhichOneLamp(uint8_t onelamp)
 *Function: be selected lamp is ON
 *Input Ref: define lamp is ON
 *Return Ref: NO
 *
***************************************************************/
void WhichOneLed_ON(uint8_t onelamp)
{
    switch(onelamp){
        
        case 1:
           
            LED1_RA0_SetHigh(); //On
            
            LED2_RA1_SetLow() ;
            LED3_RA2_SetLow() ;
            LED4_RA3_SetLow();
            LED5_RA4_SetLow() ;
            LED6_RA5_SetLow() ;
        
        break;
        
        case 2:
            
             LED2_RA1_SetHigh() ;//On
        
            LED1_RA0_SetLow(); 
           
            LED3_RA2_SetLow() ;
            LED4_RA3_SetLow();
            LED5_RA4_SetLow() ;
            LED6_RA5_SetLow() ;
        
        break;
        
        case 3:
            LED4_RA3_SetHigh(); //ON
            
            LED1_RA0_SetLow(); 
            LED2_RA1_SetLow() ;
            LED3_RA2_SetLow() ;
            
            LED5_RA4_SetLow() ;
            LED6_RA5_SetLow() ;
        
        
        break;
        
        case 4:
             LED4_RA3_SetHigh(); //ON
        
             LED1_RA0_SetLow(); 
            LED2_RA1_SetLow() ;
            LED3_RA2_SetLow() ;
           
            LED5_RA4_SetLow() ;
            LED6_RA5_SetLow() ;
        
        break;
        
        case 5:
             LED5_RA4_SetHigh() ;//ON
        
             LED1_RA0_SetLow(); 
            LED2_RA1_SetLow() ;
            LED3_RA2_SetLow() ;
            LED4_RA3_SetLow();
           
            LED6_RA5_SetLow() ;
        
        break;
        
        case 6:
            LED6_RA5_SetHigh() ; //On
        
             LED1_RA0_SetLow(); 
            LED2_RA1_SetLow() ;
            LED3_RA2_SetLow() ;
            LED4_RA3_SetLow();
            LED5_RA4_SetLow() ;
            
        
        break;
        
        default:
        
        break;
        
        
        
    }
    
    
}