#ifndef __LAMP_H_
#define __LAMP_H_
#include "key.h"

void ColorWhite_32_ON(void);
void ColorWhite_32_OFF(void);
void ColorWhite_8_ON(void);
void ColorWhite_8_OFF(void);
void Laser_ON(void);
void Laser_OFF(void);

void LED1_Power_ON(void);
void LED1_Power_OFF(void);

void LED_2_ON(void);
void LED_2_OFF(void);

void LED_3_ON(void);
void LED_3_OFF(void);

void LED_4_ON(void);
void LED_4_OFF(void);

void LED_5_ON(void);
void LED_5_OFF(void);

void LED_6_ON(void);
void LED_6_OFF(void);

void ALL_LED_OFF(void);
void TurnOff_ALL_Lamp(void);


void WhichOneColorLamp_ON(uint8_t colorlamp);
void WhichOneLed_ON(uint8_t onelamp);

void TurnOff_ALL_Lamp(void);




#endif 