#include <TaskScheduler.h>
#include "Trigger_Input.h"
#include "TunerStudio.h"
#include <LiquidCrystal.h>
#include "TimerOne.h"

#define   DEGREE_FOR_CALC   45.0
void t2Callback(void) ;
void t3Callback(void) ;

Scheduler runner;
TriggerInput _Trigger;
TunerStudio _Tunner;

Task t2(250, TASK_FOREVER, &t2Callback);
Task t3(10, TASK_FOREVER, &t3Callback);
LiquidCrystal lcd(8,9,4,5,6,7);



#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// read the buttons
int read_LCD_buttons()
{
 int adc_key_in = analogRead(0);      // read the value from the sensor 
 // my buttons when read are centered at these valies: 0, 144, 329, 504, 741
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP; 
 if (adc_key_in < 450)  return btnDOWN; 
 if (adc_key_in < 650)  return btnLEFT; 
 if (adc_key_in < 850)  return btnSELECT;  

 return btnNONE;  // when all others fail, return this...
}


void t3Callback(void) 
{
  digitalWrite(2,HIGH);
 switch (read_LCD_buttons())               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
     break;
     }
   case btnLEFT:
     {
     break;
     }
   case btnUP:
     {
      t3.setInterval(t3.getInterval()-1);
     break;
     }
   case btnDOWN:
     {
      t3.setInterval(t3.getInterval()+1);
     break;
     }
   case btnSELECT:
     {
     break;
     }
     case btnNONE:
     {
     break;
     }
 }
  digitalWrite(2,LOW);
}


void t2Callback(void) 
{
  lcd.setCursor(0,0);            // move cursor to second line "1" and 9 spaces over
  //lcd.print(_Trigger.GetFreq());
  //lcd.print(" Hz   ");
  lcd.print((uint32_t)(millis()/1000.0));
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
  Serial1.begin(9600);
  Serial.begin(115200);

  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  _Trigger.init();
  runner.addTask(t2);
  t2.enable();
    runner.addTask(t3);
  t3.enable();
}

void loop() 
{
  runner.execute();
  _Tunner.runtime();
}
