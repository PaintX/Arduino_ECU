#include "Trigger_Input.h"
#include "TimerOne.h"
#include "advance_map.h"
#include "ECU_Config.h"

unsigned long ms;
unsigned long us;

TriggerInput::s_TRIGGER   trig;
#define   JIT_DELAY_FOR_IT    100

void _DwellTime ( void )
{
  Timer1.stop();
 // digitalWrite(13,LOW);
}

void _EndOfAdvance ( void )
{
  Timer1.stop();
  //digitalWrite(13,HIGH);
  Timer1.initialize(3000);
  Timer1.attachInterrupt(_DwellTime);
}

void _EndOfCalc ( void )
{
  //-- fin des calculs
  Timer1.stop();

  Timer1.initialize(trig.advanceTime);
  Timer1.attachInterrupt(_EndOfAdvance);
  
}

void _trigPIN3(void) 
{
  us = micros();
  trig.us = us - ms;
  ms = us;

  Timer1.initialize(trig.usPerDegree * 45.0);
  Timer1.attachInterrupt(_EndOfCalc);  
  digitalWrite(13,HIGH);
  //-- debut des calculs
  trig.freq = (1.0/trig.us)*1000000.0;
  trig.usPerDegree = ((float)trig.us / 360.0);
  trig.rpm = (trig.freq * 60) / 2;
 
  trig.advanceTime = getAdvance(trig.rpm , 0);
digitalWrite(13,LOW);
}

//-- init
TriggerInput::TriggerInput()
{
  ms = 0;
  trig.us = 0;
  trig.freq = 0.0;
  pinMode(3,INPUT);
}

void TriggerInput::init(void)
{
    attachInterrupt(digitalPinToInterrupt(3), _trigPIN3, RISING); 
}

float TriggerInput::GetRpm(void)
{
  return trig.rpm;
}

float TriggerInput::GetFreq(void)
{
  return trig.freq;
}

float TriggerInput::GetUsPerDegree(void)
{
  return trig.usPerDegree;
}
void TriggerInput::SetInCalc(bool val)
{
  trig.isInCalc = val;
}

bool TriggerInput::GetInCalc(void)
{
  return trig.isInCalc;
}

void   TriggerInput::SetAdvanceTime(float time)
{
  trig.advanceTime = time;
}

float TriggerInput::GetAdvanceTime(void)
{
  return trig.advanceTime;
}
float TriggerInput::GetTimeForCal(void)
{
  return trig.usForCalc;
}

