#ifndef _TUNERSTUDIO_H_
#define _TUNERSTUDIO_H_

#if defined(ARDUINO) && ARDUINO >= 100
   #include <Arduino.h>
#else
    #include <stdint.h>
    #include <stddef.h>
    #include <stdio.h>
    #include <stdlib.h>
 //  #include <WProgram.h>
#endif

class TunerStudio
{
        #define DWELL_COUNT        8
#define IGN_LOAD_COUNT     16
#define IGN_RPM_COUNT      16
#define DWELL_CURVE_SIZE   8

    public:

        /**
        * @brief	Engine configuration.
        * 		Values in this data structure are adjustable and persisted in on-board flash RAM.
        *
        *  The offsets are tracked using
        *  https://docs.google.com/spreadsheet/ccc?key=0AiAmAn6tn3L_dGJXZDZOcVVhaG9SaHZKU1dyMjhEV0E
        *
        *  todo: currently the fields here are simply in the order in which they were implemented
        *  todo: re-arrange this structure one we have a stable code version
        */
        typedef struct
        {

            float sparkDwellBins[DWELL_COUNT]; // offset 580
            float sparkDwell[DWELL_COUNT];

            float ignitionTable[IGN_LOAD_COUNT][IGN_RPM_COUNT];
            float ignitionLoadBins[IGN_LOAD_COUNT]; // offset 3450
            float ignitionRpmBins[IGN_RPM_COUNT]; // offset 3542
            /**
            * this value could be used to offset the whole ignition timing table by a constant
            */
            float ignitionOffset;

            int16_t rpmHardLimit;
            int16_t crankingRpm;

        } engine_configuration_s;

        typedef struct
        {
            TunerStudio::engine_configuration_s engineConfiguration;
            //board_configuration_s boardConfiguration;
        } persistent_config_s;


        TunerStudio();
        void runtime(void);
        void ProcessCmd(uint8_t car);

    private:

        void _execute(void);
        void _SendIdent(void);
        void _SendSignature(void);
        void _ReadPage( void );
};

#if 0
extern persistent_config_s configWorkingCopy;
extern FlashState flashState;

#define  TUNER_BUF_SIZE 256

struct tuner_cmd_tbl_s {
	UINT8 		*name;      /* Command Name         */
	UINT16      maxargs; /* maximum number of arguments   */
	UINT16      repeatable; /* autorepeat allowed?     */
	INT16    	(*cmd)(); /* Implementation function */
	UINT8    	*usage;     /* Usage message  (short)  */
};

typedef struct tuner_cmd_tbl_s   tuner_cmd_tbl_t;



UINT8 TUNER_GetC(void);
UINT16 TUNER_ReadInt16(void);
void TUNER_PutC(UINT8 car);
void TUNER_PutS(char * pFormat,...);
void TUNER_Put(UINT8* buffer,int size);
void TUNERSTUDIO_Init(void);
void TUNERSTUDIO_Sync(void) ;

#endif
#endif
