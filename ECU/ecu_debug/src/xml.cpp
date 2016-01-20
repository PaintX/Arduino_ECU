#include "xml.h"
#include "../../ECU_Config.h"

#include <fstream>
#include "pugixml.hpp"

xml xmlfile;
char tabFilePath[ MAX_PATH ];

uint8_t     memfile[1024];

xml::xml()
{
    //ctor
/*
    char pathy[ MAX_PATH ];
    GetCurrentDirectory( MAX_PATH, pathy );

    sprintf(tabFilePath,"%s\\%s",pathy,"table.table");

    pugi::xml_document doc;
    doc.load_file(tabFilePath);

    pugi::xml_text txt = doc.child("tableData").child("table").child("xAxis").text();*/


    for ( int i = 0 ; i < IGN_RPM_COUNT ; i++)
    {
        for ( int j = 0 ; j < IGN_LOAD_COUNT ; j++)
        {
            flashState.engineConfiguration.ignitionTable[i][j] = 13;
        }
    }

    for ( int i = 0 ; i < IGN_RPM_COUNT ; i++)
        flashState.engineConfiguration.ignitionRpmBins[i] = i * 500;

    for ( int i = 0 ; i < IGN_LOAD_COUNT ; i++)
        flashState.engineConfiguration.ignitionLoadBins[i] = i * 10;


    uint8_t * ptr =  (uint8_t*)&flashState.engineConfiguration;
    for ( int i = 0 ; i < sizeof(engine_configuration_s) ; i++)
    {
        memfile[i] = ptr[i];
    }
}

xml::~xml()
{
    //dtor
}



void xml::update(int i , uint8_t val)
{
    memfile[i] = val;
}

uint8_t xml::read(int i)
{
    return memfile[i];
}
