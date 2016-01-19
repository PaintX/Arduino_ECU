#include "xml.h"
#include "../../ECU_Config.h"

#include <fstream>


xml xmlfile;

xml::xml()
{
    //ctor
}

xml::~xml()
{
    //dtor
}


void xml::update(int i , uint8_t val)
{

}

char * getexepath()
{
  char result[ MAX_PATH ];
  GetModuleFileName( NULL, result, MAX_PATH );
  Cons.print(result);
  return result;
}

uint8_t xml::read(int i)
{
    char result2[ MAX_PATH ];
    char result[ MAX_PATH ];
    GetCurrentDirectory( MAX_PATH, result );

    sprintf(result2,"%s\\%s",result,"table.table");
    FILE * fp = fopen("table2.table","r");
    //fwrite(result2,1,5,fp);
   /* std::ifstream infile("table.table");

  if (infile.is_open())
  {
      Cons.print("is open");
  }*/
/*
    infile.open ("table.table");
    for( std::string line; getline( infile, line ); )
    {

    }
    */
    fclose(fp);
}
