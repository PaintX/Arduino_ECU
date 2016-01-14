#include "Trigger_Input.h"
#include "TimerOne.h"


TriggerInput _Trigger;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  _Trigger.init();
  
}

void loop() 
{
  // put your main code here, to run repeatedly:

}
