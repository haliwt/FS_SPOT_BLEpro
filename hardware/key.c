#include "key.h"
#include "run.h"
KEY_T key_t;
uint8_t   KEY_Scan(void)
{
    static uint16_t  k1=0 ;
    static uint16_t  k2=0 ;
    static uint16_t  k3=0 ;
    static uint16_t  k4=0 ;
    static uint16_t  k5=0 ;
	static uint16_t  k6=0 ;
    uint8_t cnt;
#if 0
   if(POWER_KEY_RB0_GetValue() ==0){
        if(k1<181)
        k1++;   
    }
    else {  
      k1=0;  
    }
#endif 
    if(KEY_LAMP_1_RB1_GetValue() ==0){
       if(k2<181)
        k2++; 
       
    }
    else{
        
        k2=0; 
    }  
    
    if(KEY_LAMP_2_RB2_GetValue() ==0){
       if(k3<181)
        k3++; 
       
    }
    else{
        
        k3=0; 
    }
    if(KEY_LASER_RB5_GetValue() ==0){ // laser 0x08
       if(k4<181)
        k4++; 
       
    }
    else{
        
        k4=0; 
    } 
    if(KEY_ADD_RB3_GetValue() ==0){ //add "+" 0x20
       if(k5<181)
        k5++; 
       
    }
    else{
        
        k5=0; 
    }  
    if(KEY_SUB_RB4_GetValue() ==0){ //sub "-"  0x10
       if(k6<181)
        k6++; 
    }
    else{
        
        k6=0; 
    } 
    
	
    /***************************/
#if 0
    if(k1==180){
       cnt= 0x1  ;  //power key
      // k1=0; //BUG
       return cnt ;
    }
#endif 
    if(k2==180){
        cnt= 0x2  ; //key color white lamp 1  0x02
       // k2=0;
        return cnt ;
    }
    if(k3==180){
        cnt= 0x4  ;  //key color white lamp 2 0x04
       // k3=0;
        return cnt ;
    }
    if(k4==180){
	  cnt =0x08;      // key laser 0x08
	 // k6=0;
      return cnt ;
	}
    if(k5==180){
        cnt= 0x20  ;  //KEY_ADD +
     //   k4=0;
        return cnt ;
    }
    if(k6==180){
        cnt= 0x10 ;   //KEY_SUB -
      //  k5=0;
        return cnt ;
    }
	
    return 0 ;
    
}


void PowrKEY_ISR(void)
{
    static uint8_t k1;
    
  
   
          k1 = k1^ 0x01;
          if(k1==1){
             
             run_t.gRunOrder= powerON; 
          }
          else{ 
             run_t.gRunOrder= noLamp; 
          }
    
   

}



