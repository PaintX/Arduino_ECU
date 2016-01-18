
//#include <stdarg.h>
#include "TunerStudio.h"
#include "Trigger_Input.h"
#include "Variables.h"
#include "ECU_Config.h"


//#define  DEBUG_TUNERSTUDIO


//---------- Variables ----------
  
  char _getC(void)
  {
    while( !SERIAL_PORT.available() ){}
    return SERIAL_PORT.read();
  }
    #define COMM_AVAILABLE_CHAR()       (SERIAL_PORT.available() > 0)
    #define COMM_GET_CHAR()             _getC()
    #define COMM_WRITE(X,Y)             SERIAL_PORT.write(X,Y); SERIAL_PORT.flush()
    #define COMM_SEND(X)                SERIAL_PORT.print(X); SERIAL_PORT.flush()


extern TriggerInput _Trigger;
/**
 * this is a local copy of the configuration. Any changes to this copy
 * have no effect until this copy is explicitly propagated to the main working copy
 */
TunerStudio::persistent_config_s        configWorkingCopy;
TunerStudio::TunerStudioOutputChannels  tsOutputChannels;
TunerStudio::persistent_config_s        flashState;


uint16_t _ReadInt16(void)
{
   uint8_t val8;
   uint16_t val16;

   val16 = 0;
   val8 = COMM_GET_CHAR();
   val16 |= COMM_GET_CHAR();
   val16 = val16 << 8;
   val16 |= val8;

   return val16;
}
int _getTunerStudioPageSize(int pageIndex)
{
	switch (pageIndex)
	{
        case 0:
            return sizeof(configWorkingCopy.engineConfiguration);
    /*	case 1:
            return sizeof(configWorkingCopy.boardConfiguration);*/
    }
	return 0;
}

char *_getWorkingPageAddr(int pageIndex) {
	switch (pageIndex) {
	case 0:
		return (char*) &configWorkingCopy.engineConfiguration;
/*	case 1:
		return (char*) &configWorkingCopy.boardConfiguration;*/
	}
	return NULL;
}

TunerStudio::TunerStudio()
{
    #if defined(ARDUINO)

    #if 0
      //-- creation d'une tache
      for ( int i = 0 ; i < IGN_LOAD_COUNT ; i++ )
      {
        for ( int j = 0 ; j < IGN_RPM_COUNT ; j++ )
        {
          flashState.engineConfiguration.ignitionTable[i][j] = 0.0 + j;
        }
      }
  
      flashState.engineConfiguration.ignitionLoadBins[0] = 0;
      flashState.engineConfiguration.ignitionLoadBins[1] = 1013;
  
      for ( int i = 0 ; i < IGN_RPM_COUNT ; i++ )
        flashState.engineConfiguration.ignitionRpmBins[i] = i * 500.0;
        
      for ( int i = 0 ; i < IGN_LOAD_COUNT ; i++ )    
        flashState.engineConfiguration.ignitionLoadBins[i] = i * 100;
        
      flashState.engineConfiguration.ignitionOffset = 0.0;
    #else
      uint8_t * ptr =  (uint8_t*)&flashState.engineConfiguration;
      for (int i = 0 ; i < sizeof(engine_configuration_s) ; i++ )
      {
        ptr[i] = EEPROM.read(i);
      }
    #endif
    #endif // defined
}


void TunerStudio::runtime(void)
{
    if ( COMM_AVAILABLE_CHAR() )
    {
        ProcessCmd(COMM_GET_CHAR());
    }
}

void TunerStudio::ProcessCmd(uint8_t car)
{
    _UpdateValue();
    switch ( car )
    {
        case ( 'Q' ):
        {
          #ifdef DEBUG_TUNERSTUDIO
          SERIAL_DEBUG.println("Q");
          #endif
            _SendIdent();
           //_SendSignature();
            break;
        }
        case ( 'H' ):
        {
          #ifdef DEBUG_TUNERSTUDIO
          SERIAL_DEBUG.println("H");
          #endif
          _SendSignature();
          break;
        }
        case ( 'S' ):
        {
          #ifdef DEBUG_TUNERSTUDIO
            SERIAL_DEBUG.println("S");
            #endif
            _SendSignature();
            break;
        }
        case ( 'C' ):
        {
          #ifdef DEBUG_TUNERSTUDIO
          SERIAL_DEBUG.println("C");
          #endif
          _ReadPage();
          break;
        }
        case ( 'O' ):
        {
          #ifdef DEBUG_TUNERSTUDIO
          SERIAL_DEBUG.println("O");
          #endif
          _OutputChannel();
          break;
        }
        case ( 'W' ):
        {
          #ifdef DEBUG_TUNERSTUDIO
          SERIAL_DEBUG.println("W");
          #endif
          _WritePage();
            break;
        }
        case ( 'F' ):
        {
          #ifdef DEBUG_TUNERSTUDIO
          SERIAL_DEBUG.println("F");
          #endif
            break;
        }
        case ( 'B' ):
        {
          #ifdef DEBUG_TUNERSTUDIO
          SERIAL_DEBUG.println("B");
          #endif
          _SavePage();
            break;
        }
    }
}

void TunerStudio::_SendIdent(void)
{
  #ifdef DEBUG_TUNERSTUDIO
  SERIAL_DEBUG.print("ECUFor126     8.0.0");
  #endif
  COMM_SEND("ECUFor126     8.0.0");
}
void TunerStudio::_SendSignature(void)
{
  
    COMM_SEND("MShift v0.01");
    #ifdef DEBUG_TUNERSTUDIO
    SERIAL_DEBUG.print("MShift v0.01");
    #endif
}

void  TunerStudio::_ReadPage( void )
{
    uint16_t pageId,i;
    uint32_t sizePage;
    char* ptr;
    
    pageId = _ReadInt16();
    sizePage = _getTunerStudioPageSize(pageId);
    ptr = _getWorkingPageAddr(pageId);

    COMM_WRITE(ptr,sizePage);
}

void TunerStudio::_OutputChannel( void )
{
  COMM_WRITE((uint8_t*)&tsOutputChannels,sizeof(TunerStudioOutputChannels));
}



void TunerStudio::_UpdateValue( void )
{
   /*tsOutputChannels.rpm =                       RPM_GetVal();
   tsOutputChannels.coolant_temperature =       COOLANT_GetVal();
   tsOutputChannels.atmospherePressure =        ATMO_GetVal();
   tsOutputChannels.manifold_air_pressure =     MAP_GetVal();*/

   tsOutputChannels.rpm = _Trigger.GetRpm();
   tsOutputChannels.advance = _Trigger.GetAdvanceTime();
   tsOutputChannels.coolant_temperature = _Trigger.GetAdvanceTime();
   tsOutputChannels.vBatt = analogRead(0);
   tsOutputChannels.vBatt *= (float)(5.0/1023.0);
   tsOutputChannels.vBatt += 7.0;
}


/**
 * 'Write' command receives a single value at a given offset
 */
void TunerStudio::_WritePage( void )
{
  uint16_t pageId;
  uint32_t   offset;
  uint8_t    value;
  
  pageId = _ReadInt16();
  offset = _ReadInt16();
  value = COMM_GET_CHAR();
  _getWorkingPageAddr(pageId)[offset] = value;

}


void TunerStudio::_SavePage( void )
{
   uint16_t pageId;
   pageId = _ReadInt16();

   // todo: how about some multi-threading?
    memcpy(&flashState, &configWorkingCopy, sizeof(persistent_config_s));

    uint8_t * ptr =  (uint8_t*)&flashState.engineConfiguration;
    for (int i = 0 ; i < sizeof(engine_configuration_s) ; i++ )
    {
      EEPROM.update(i,ptr[i]);
    }
      
  //CONFIG_Save();
}

