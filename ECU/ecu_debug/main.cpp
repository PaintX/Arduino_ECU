#include <stdio.h>
#include "../Advance_Table.h"



AdvanceTable adv;

int main()
{
    int val = adv.get3DTableValue(0,1600);

    printf("%d \r\n ",val);
    return 0;
}
