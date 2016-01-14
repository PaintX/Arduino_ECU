#ifndef _TRIGGER_INPUT_H_
#define _TRIGGER_INPUT_H_

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
          unsigned int    us;
          float           freq;
        } s_TRIGGER;

      //****************************
      //  Configuration
      //****************************
      
         // constructor
         TriggerInput();

         void init(void);
   };
#endif

