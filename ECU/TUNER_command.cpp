//=============================================================================
//
// PROJET       : POSTE FIXE 2013
// MODULE       : main.c
// DESCRIPTION  : initialisation et lancement de l'application
//
//-----------------------------------------------------------------------------
//
// HISTORIQUE   :
//
// 	11.04.2012 - V0.01 : - Creation
//
//=============================================================================

//=============================================================================
//--- DECLARATIONS
//=============================================================================

//-----------------------------------------------------------------------------
// Fichiers Inclus
//-----------------------------------------------------------------------------
#if 0
#include "TunerStudio.h"
#include "TUNER_command.h"
#include "tunerstudio_configuration.h"


const INT8 RevNum[] = {     // revision no:
// only change for major rev and/or interface change.
// Change the numeric prefix if the raw data becomes incompatible.
// Change the dotted suffix if the ini changes, but data remains compatible
    "EfiFreeRtos   8.0.0"
  //"1234567890123456789"
};
const INT8 Signature[] = {            // program title.
    // Change this every time you tweak a feature.
    "MShift v0.01"
  //"12345678901234567890123456789012345678901234567890123456789"
};


/**
 * this is a local copy of the configuration. Any changes to this copy
 * have no effect until this copy is explicitly propagated to the main working copy
 */
persistent_config_s        configWorkingCopy;
TunerStudioOutputChannels  tsOutputChannels;

//-----------------------------------------------------------------------------
// Fonctions
//-----------------------------------------------------------------------------

void TUNER_SendIdent ( void )
{
   /* serial format */
   TUNER_PutS("%s",RevNum);
}

void TUNER_SendSignature( void )
{
   /* serial format */
   TUNER_PutS("%s",Signature);
}

int getTunerStudioPageSize(int pageIndex) {
	switch (pageIndex) {
	case 0:
		return sizeof(configWorkingCopy.engineConfiguration);
/*	case 1:
		return sizeof(configWorkingCopy.boardConfiguration);*/
	}
	return 0;

}

char *getWorkingPageAddr(int pageIndex) {
	switch (pageIndex) {
	case 0:
		return (char*) &configWorkingCopy.engineConfiguration;
/*	case 1:
		return (char*) &configWorkingCopy.boardConfiguration;*/
	}
	return NULL;
}

void TUNER_ReadPage( void )
{
   UINT16 pageId,i;
   UINT32 sizePage;
   char* ptr;
   pageId = TUNER_ReadInt16();

   sizePage = getTunerStudioPageSize(pageId);
   ptr = getWorkingPageAddr(pageId);

   TUNER_Put(ptr,sizePage);
}

/**
 * 'Write' command receives a single value at a given offset
 */
void TUNER_WritePage( void )
{
   UINT32   offset;
   UINT8    value;
   UINT16 pageId;
   pageId = TUNER_ReadInt16();

   offset = TUNER_ReadInt16();
   value = TUNER_GetC();

   getWorkingPageAddr(pageId)[offset] = value;
}

void TUNER_OutputChannel( void )
{
   TUNER_Put((UINT8*)&tsOutputChannels,sizeof(TunerStudioOutputChannels));
}

void TUNER_SavePage( void )
{
   UINT16 pageId;
   pageId = TUNER_ReadInt16();

   // todo: how about some multi-threading?
	memcpy(&flashState.persistentConfiguration, &configWorkingCopy, sizeof(persistent_config_s));

	CONFIG_Save();
}

//-----------------------------------------------------------------------------
// Constantes
//-----------------------------------------------------------------------------
static const tuner_cmd_tbl_t _tuner_cmd[] =
{
   {"Q"           ,1       ,0       ,TUNER_SendIdent        ,"Envoi de l'identification"},
   {"H"           ,1       ,0       ,TUNER_SendSignature    ,"Envoi de l'identification"},
   {"S"           ,1       ,0       ,TUNER_SendSignature    ,"Envoi de l'identification"},
   {"C"           ,1       ,0       ,TUNER_ReadPage         ,"Lecture d'une page de config"},
   {"O"           ,1       ,0       ,TUNER_OutputChannel    ,"Lecture des données de ECU"},
   {"W"           ,1       ,0       ,TUNER_WritePage        ,"Ecriture des données de ECU"},
   {"F"           ,1       ,0       ,NULL                   ,""},
   {"B"           ,1       ,0       ,TUNER_SavePage         ,"Sauvegarde des données de ECU"},
};

//-----------------------------------------------------------------------------
// Variables globales
//-----------------------------------------------------------------------------
//=============================================================================
//--- DEFINITIONS
//=============================================================================

void TUNER_UpdateValue(void)
{
   tsOutputChannels.rpm =                       RPM_GetVal();
   tsOutputChannels.coolant_temperature =       COOLANT_GetVal();
   tsOutputChannels.atmospherePressure =        ATMO_GetVal();
   tsOutputChannels.manifold_air_pressure =     MAP_GetVal();
   tsOutputChannels.v_batt = 12.52;
}

//-----------------------------------------------------------------------------
// FONCTION    : CMD_process
//
// DESCRIPTION : gestion de la commande
//-----------------------------------------------------------------------------
INT16 TUNER_CMD_process(UINT8 cmd)
{
   UINT8 tab[2];
   UINT16 i;

   /* mise a jours des infos pour tuner studio */

   TUNER_UpdateValue();

   for ( i = 0 ; i < ARRAY_SIZE(_tuner_cmd) ; i++)
   {
      tab[0] = cmd;
      tab[1] = 0;
      if ( strcmp(tab,_tuner_cmd[i].name) == 0)
      {
         if ( _tuner_cmd[i].cmd != NULL )
            _tuner_cmd[i].cmd();
      }
   }
}
#endif
