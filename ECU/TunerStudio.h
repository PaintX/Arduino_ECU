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






   /**
     * please be aware that 'float' (F32) type requires TunerStudio version 2.6 and later
     */
    typedef struct {
        // primary instrument cluster gauges
          uint32_t rpm; // size 4, offset 0
        float coolant_temperature; // size 4, offset 4
        float intakeAirTemperature; // size 4, offset 8
        float throttlePositon; // size 4, offset 12
        float massAirFlowVoltage; // size 4, offset 16
        float airFuelRatio; // size 4, offset 20
        float engineLoad; // size 4, offset 24
        float vBatt; // size 4, offset 28
        short int tpsADC; // size 2, offset 32
        short int alignment; // size 2, offset 34
        float baroPressure; // size 4, offset 36
        float manifold_air_pressure; // size 4, offset 40
        uint32_t  checkEngine; // size 4, offset 44
   } TunerStudioOutputChannels;



  
        TunerStudio();
        void runtime(void);
        void ProcessCmd(uint8_t car);

    private:

        //void _execute(void);
        void _SendIdent(void);
        void _OutputChannel( void );
        void _SendSignature(void);
        void _ReadPage( void );
        void _UpdateValue( void );
        void _WritePage( void );
        void _SavePage( void );
};
#endif
