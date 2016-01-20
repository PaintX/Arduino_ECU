#include "ECU_Config.h"
#include "Trigger_Input.h"
#include "advance_map.h"

#define     SIMU_TRIGGER

static s_TRIGGER  _trig;
static uint32_t _us;

void _TrigISR(void)
{
  uint32_t us = MICROS();
  _trig.us = us - _us;
  _us = us;

#ifndef SIMU_TRIGGER
  Timer1.initialize(trig.usPerDegree * 45.0);
  Timer1.attachInterrupt(_EndOfCalc);
#endif

    //-- debut des calculs
    _trig.freq = (1.0/_trig.us)*1000000.0;
    //_trig.usPerDegree = ((float)_trig.us / 360.0);
    _trig.rpm = (_trig.freq * 60) / 2;

    _trig.usPerDegree = IGN_GetOneDegreeUs(_trig.rpm);
    _trig.advanceTime = IGN_GetAdvance(_trig.rpm , 0);

    //-- dwell de la bobine en fonction de la table
    float dwellMs =     IGN_GetSparkDwellMs(_trig.rpm);
	if (dwellMs <= 0.0)
		return; // hard RPM limit was hit
}

float TRIGGER_GetAdvanceTime(void)
{
  return _trig.advanceTime;
}

float TRIGGER_GetRpm(void)
{
  return _trig.rpm;
}

float TRIGGER_GetFreq(void)
{
    return _trig.freq;
}
static uint32_t us = MICROS();
void TRIGGER_Init(void)
{
    us = MICROS();
#ifndef SIMU_TRIGGER

    pinMode(3,INPUT);
    attachInterrupt(digitalPinToInterrupt(3), _trigPIN3, RISING);
#endif
}

void TRIGGER_Execute(void)
{
#ifdef SIMU_TRIGGER

    //-- pour simulation
    uint32_t test = MICROS();
    if ( (uint32_t)(test - us ) >= (uint32_t)20000 )
    {
        _TrigISR();
        us = MICROS();
    }
#endif
}




#if 0

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
#endif
