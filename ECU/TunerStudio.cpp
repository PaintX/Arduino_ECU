
//#include <stdarg.h>
#include "TunerStudio.h"
#include "Trigger_Input.h"
//#include "TUNER_command.h"
//---------- Variables ----------
#if defined(ARDUINO)

#define   SERIAL_PORT       Serial1
#define   SERIAL_DEBUG       Serial
  char _getC(void)
  {
    while( !SERIAL_PORT.available() ){}
    return SERIAL_PORT.read();
  }
    #define COMM_AVAILABLE_CHAR()       (SERIAL_PORT.available() > 0)
    #define COMM_GET_CHAR()             _getC()
    #define COMM_WRITE(X,Y)             SERIAL_PORT.write(X,Y); SERIAL_PORT.flush()
    #define COMM_SEND(X)                SERIAL_PORT.print(X); SERIAL_PORT.flush()
#else
    #define COMM_AVAILABLE_CHAR()       true
    #define COMM_GET_CHAR()             getchar()
    #define COMM_WRITE(X,Y)
#endif // defined


extern TriggerInput _Trigger;
/**
 * this is a local copy of the configuration. Any changes to this copy
 * have no effect until this copy is explicitly propagated to the main working copy
 */
TunerStudio::persistent_config_s        configWorkingCopy;
TunerStudio::TunerStudioOutputChannels  tsOutputChannels;

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
    //-- creation d'une tache

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
          SERIAL_DEBUG.println("Q");
            _SendIdent();
           //_SendSignature();
            break;
        }
        case ( 'H' ):
        {
          SERIAL_DEBUG.println("H");
          _SendSignature();
          break;
        }
        case ( 'S' ):
        {
            SERIAL_DEBUG.println("S");
            _SendSignature();
            break;
        }
        case ( 'C' ):
        {
          SERIAL_DEBUG.println("C");
          _ReadPage();
          break;
        }
        case ( 'O' ):
        {
          SERIAL_DEBUG.println("O");
          _OutputChannel();
          break;
        }
        case ( 'W' ):
        {
          SERIAL_DEBUG.println("W");
          _WritePage();
            break;
        }
        case ( 'F' ):
        {
          SERIAL_DEBUG.println("F");
            break;
        }
        case ( 'B' ):
        {
          SERIAL_DEBUG.println("B");
          _SavePage();
            break;
        }
    }
}

void TunerStudio::_SendIdent(void)
{
  SERIAL_DEBUG.print("ECUFor126     8.0.0");
  COMM_SEND("ECUFor126     8.0.0");
}
void TunerStudio::_SendSignature(void)
{
    COMM_SEND("MShift v0.01");
    SERIAL_DEBUG.print("MShift v0.01");
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

   tsOutputChannels.rpm = (_Trigger.GetFreq() * 60) / 2;
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

/*
  SERIAL_DEBUG.print("page id : ");
  SERIAL_DEBUG.println(pageId);
  SERIAL_DEBUG.print("offset : ");
  SERIAL_DEBUG.println(offset);
  SERIAL_DEBUG.print("value : ");
  SERIAL_DEBUG.println(value);*/
}


void TunerStudio::_SavePage( void )
{
   uint16_t pageId;
   pageId = _ReadInt16();

   // todo: how about some multi-threading?
    //memcpy(&flashState.persistentConfiguration, &configWorkingCopy, sizeof(persistent_config_s));

  //CONFIG_Save();
}

