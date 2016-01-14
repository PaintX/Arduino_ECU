#include "Trigger_Input.h"

unsigned long ms;
unsigned long us;
TriggerInput::s_TRIGGER   trig;

void _trigPIN3(void) 
{
  us = micros();
  trig.us = us - ms;
  ms = us;
}


//-- init
TriggerInput::TriggerInput()
{
  ms = 0;
  trig.us = 0;
  trig.freq = 0.0;
}

void TriggerInput::init(void)
{
    attachInterrupt(digitalPinToInterrupt(3), _trigPIN3, RISING); 
}



