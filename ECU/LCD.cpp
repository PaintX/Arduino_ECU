#include "LCD.h"

#ifdef ARDUINO
    LiquidCrystal lcd(8,9,4,5,6,7);
#else

#endif // ARDUINO

static uint32_t _Tick;
static uint16_t _Periode = 1000;

static void _Refresh(void)
{
    LCD_SetPosition(0,0);
    LCD.print("RPM : ");
    LCD.print(TRIGGER_GetRpm());
    LCD_SetPosition(0,1);
    LCD.print("ADV : ");
    LCD.print(TRIGGER_GetAdvanceTime());
}

void LCD_Init(int col , int lin)
{
    LCD.begin(16,2);
    _Tick = MILLIS();
}


void LCD_SetRefreshPeriode(uint16_t ms)
{
    _Periode = ms;
}


void LCD_Execute(void)
{
    if ( (MILLIS() - _Tick) >= _Periode)
    {
        _Refresh();
        _Tick = MILLIS();
    }
}

void LCD_SetPosition(uint8_t x , uint8_t y)
{
    LCD.setCursor(x,y);
}

