#ifndef __KEY_H_
#define __KEY_H_
#include"../mcc_generated_files/mcc.h"


typedef struct {
  
   
    uint8_t gColorWhite_32;
    uint8_t gColorWhite_8;
    
    
}KEY_T;
extern  KEY_T key_t;
uint8_t KEY_Scan(void);



#endif 