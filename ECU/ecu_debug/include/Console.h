#ifndef CONSOLE_H
#define CONSOLE_H

#include "ECU_Config.h"

class Console
{
    public:
        Console();
        virtual ~Console();

        void begin(int val);
        bool available(void);
        uint8_t read(void);
        void print(char * str);
        void print(float val);
        void print(float val,int dec);
        void println(char * str);
        void println(float val,int dec);
        void println(float val);
        void write(uint8_t * tab , uint16_t size);
    protected:
    private:
};

extern Console Cons;

#endif // CONSOLE_H
