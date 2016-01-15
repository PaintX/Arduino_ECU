
#include <stdarg.h>
#include "TunerStudio.h"
#include "TUNER_command.h"
//---------- Variables ----------
#if defined(ARDUINO)

char _getC(void)
{
  while( !Serial.available() ){}
  return Serial.read();
}
    #define COMM_AVAILABLE_CHAR()       (Serial.available() > 0)
    #define COMM_GET_CHAR()             _getC()
    #define COMM_WRITE(X,Y)             Serial.write(X,Y)
#else
    #define COMM_AVAILABLE_CHAR()       true
    #define COMM_GET_CHAR()             getchar()
    #define COMM_WRITE(X,Y)
#endif // defined

/**
 * this is a local copy of the configuration. Any changes to this copy
 * have no effect until this copy is explicitly propagated to the main working copy
 */
TunerStudio::persistent_config_s        configWorkingCopy;


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
    switch ( car )
    {
        case ( 'Q' ):
        {
            _SendIdent();
            break;
        }
        case ( 'H' ):
        case ( 'S' ):
        {
            _SendSignature();
            break;
        }
        case ( 'C' ):
        {
            _ReadPage();
            break;
        }
        case ( 'O' ):
        {
            break;
        }
        case ( 'W' ):
        {
            break;
        }
        case ( 'F' ):
        {
            break;
        }
        case ( 'B' ):
        {
            break;
        }
    }
}

void TunerStudio::_SendIdent(void)
{
    printf("EfiFreeRtos   8.0.0");
}
void TunerStudio::_SendSignature(void)
{
    printf("MShift v0.01");
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
  /* char* ptr;
   pageId = TUNER_ReadInt16();

   sizePage = getTunerStudioPageSize(pageId);
   ptr = getWorkingPageAddr(pageId);

   TUNER_Put(ptr,sizePage);
   */
}

#if 0
UINT8 TUNER_GetC(void)
{
   UINT8 tab[2];
   tab[1] = 0;
   CDCTxService();
   while ( getsUSBUSART(tab,1) != 1){CDCTxService();vTaskDelay(1);}
   return tab[0];
}

UINT16 TUNER_ReadInt16(void)
{
   UINT8 val8;
   UINT16 val16;

   val16 = 0;
   val8 = TUNER_GetC();
   val16 |= TUNER_GetC();
   val16 = val16 << 8;
   val16 |= val8;

#if 0
   val16 = 0;
   val8 = TUNER_GetC();
   val16 = val8;
   val16 = val16 << 8;
   val16 |= TUNER_GetC();
#endif
   return val16;
}
void TUNER_PutC(UINT8 car)
{
   UINT8 tab[2];
   tab[0] = car;
   tab[1] = 0;
   CDCTxService();
   while ( !mUSBUSARTIsTxTrfReady()){CDCTxService();}
   putUSBUSART(tab,1);
   CDCTxService();
}

void TUNER_PutS(char * pFormat,...)
{
   UINT8 buff[TUNER_BUF_SIZE];
   va_list ap;
   UINT16 i = 0;

   /* Forward call to vprintf */
   va_start(ap, pFormat);
   vsprintf(buff, pFormat, ap);
   va_end(ap);

   while ( buff[i] != '\0' )
   {
      TUNER_PutC(buff[i]);
      i++;
   }
}

void TUNER_Put(UINT8* buffer,int size)
{
   UINT16 i = 0;
   for ( i = 0 ; i < size ; i++ )
   {
      TUNER_PutC(buffer[i]);
   }
}

void TUNERSTUDIO_Sync(void)
{
	memcpy(&configWorkingCopy, &flashState.persistentConfiguration, sizeof(persistent_config_s));
}

portTASK_FUNCTION( _TunerThread, pvParameters )
{

   while ( TRUE )
   {
      if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) continue;
      TUNER_CMD_process(TUNER_GetC());
   }
}

#endif
