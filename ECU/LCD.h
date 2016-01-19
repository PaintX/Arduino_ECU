#ifndef _LCD_H_
#define _LCD_H_

#include "ECU_Config.h"

void LCD_Init(int col , int lin);
void LCD_SetRefreshPeriode(uint16_t ms);
void LCD_Execute(void);
void LCD_SetPosition(uint8_t x , uint8_t y);
#endif
