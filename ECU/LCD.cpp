#include "LCD.h"

#ifdef ARDUINO
    LiquidCrystal lcd(8,9,4,5,6,7);
#endif // ARDUINO

static uint32_t _Tick;
static uint16_t _Periode = 1000;

static void _Refresh(void)
{
    SERIAL_PORT.print("RPM :");
    SERIAL_PORT.println(TRIGGER_GetFreq());
}

void LCD_Init(int col , int lin)
{
#ifdef ARDUINO
    lcd.begin(16,2);
#endif // ARDUINO
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
