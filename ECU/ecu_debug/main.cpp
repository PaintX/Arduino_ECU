#include <stdio.h>
#include "xml.h"
#include "Console.h"


void setup();
void loop();

int main()
{
    setup();
    while ( 1 )
    {
        loop();
    }
}

#include "../ECU.ino"
