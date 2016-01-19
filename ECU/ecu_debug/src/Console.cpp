#include "Console.h"
#include "../../ECU_Config.h"



Console Cons;

Console::Console()
{
    //ctor
}

Console::~Console()
{
    //dtor
}

void Console::begin(int val)
{

}

void Console::print(char * str)
{
    printf("%s",str);
}

void Console::print(float val)
{
    printf("%0.2f",val);
}

void Console::print(float val,int dec)
{
    printf("%0.*f",dec,val);
}

void Console::println(char * str)
{
    printf("%s\r\n",str);
}

void Console::println(float val)
{
    printf("%0.2f\r\n",val);
}

void Console::println(float val,int dec)
{
    printf("%0.*f\r\n",dec,val);
}


bool Console::available(void)
{
    if ( kbhit() > 0)
        return true;
    else
        return false;
}

uint8_t Console::read(void)
{
    return getche();
}


void Console::write(uint8_t * tab , uint16_t size)
{
    for ( uint16_t i = 0 ; i < size ; i++ )
    {
        printf("%c" , tab[i]);
    }
}
