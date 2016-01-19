#ifndef _TRIGGER_INPUT_H_
#define _TRIGGER_INPUT_H_

typedef struct
{
    float     us;
    float     freq;
    float     usPerDegree;
    bool      isInCalc;
    float     advanceTime;
    float     usForCalc;
    float     rpm;

} s_TRIGGER;


void TRIGGER_Init(void);
void TRIGGER_Execute(void);

float TRIGGER_GetFreq(void);





#if 0
#if defined(ARDUINO) && ARDUINO >= 100
   #include <Arduino.h>
#else
   #include <WProgram.h>
#endif

   class TriggerInput
   {
      public:
        typedef struct
        {
          float     us;
          float     freq;
          float     usPerDegree;
          bool      isInCalc;
          float     advanceTime;
          float     usForCalc;
          float     rpm;

        } s_TRIGGER;

      //****************************
      //  Configuration
      //****************************

         // constructor
         TriggerInput();

         void   init(void);
         float  GetFreq(void);
         float  GetUsPerDegree(void);
         bool   GetTrigged(void);
         void   SetInCalc(bool val);
         bool   GetInCalc(void);
        float GetAdvanceTime(void);
         void   SetAdvanceTime(float time);
         float  GetTimeForCal(void);
         float GetRpm(void);
   };
   #endif
#endif

