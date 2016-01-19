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

void Console::begin(uint8_t x, uint8_t y)
{
    _COORD coord;
    coord.X = x;
    coord.Y = y;

    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = coord.Y - 1;
    Rect.Right = coord.X - 1;

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size
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

void Console::setCursor(uint8_t x, uint8_t y)
{

    HANDLE hStdOut = ::GetStdHandle(STD_OUTPUT_HANDLE); // console output handle
    COORD dwCursorPosition;
    DWORD nb;
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    ::SetConsoleCursorPosition(hStdOut,dwCursorPosition);
    //::WriteConsoleOutputCharacter(hStdOut, _T("foo_bar"), 7, dwCursorPosition, &nb);
}
