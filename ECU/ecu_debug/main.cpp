#include <stdio.h>
#include "../Advance_Table.h"
#include "../TunerStudio.h"


AdvanceTable adv;
TunerStudio     _Tuner;
int main()
{
    while ( true )
    {
       _Tuner.execute();
    }
    return 0;
}
