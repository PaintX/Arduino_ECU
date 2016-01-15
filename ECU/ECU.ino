#include <TaskScheduler.h>
#include "Trigger_Input.h"
#include "TunerStudio.h"
#include <LiquidCrystal.h>
#include "TimerOne.h"

#define   DEGREE_FOR_CALC   45.0

Scheduler runner;
TriggerInput _Trigger;
TunerStudio _Tunner;
Task t2(250, TASK_FOREVER, &t2Callback);
LiquidCrystal lcd(8,9,4,5,6,7);

void t2Callback(void) 
{
  lcd.setCursor(0,0);            // move cursor to second line "1" and 9 spaces over
  lcd.print(_Trigger.GetFreq());
  lcd.print(" Hz   ");
  lcd.setCursor(0,1);            // move cursor to second line "1" and 9 spaces over
  
  lcd.print( (_Trigger.GetFreq() * 60) / 2 );
  lcd.print(" rpm   ");
  
  // put your main code here, to run repeatedly:
  //Serial.print(_Trigger.GetFreq());
  //Serial.print(" Hz ");
  //float delay_ms = _Trigger.GetUsPerDegree() * DEGREE_FOR_CALC;
  //Serial.print(delay_ms);
  //Serial.println(" us ");

  //Serial.print(_Trigger.GetTimeForCal());
  //Serial.println(" us "); 
}



void setup() 
{
  lcd.begin(16,2);
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  _Trigger.init();
  runner.addTask(t2);
  t2.enable();
}

void loop() 
{
  runner.execute();
  _Tunner.runtime();
}
