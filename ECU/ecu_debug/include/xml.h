#ifndef XML_H
#define XML_H

#include "ECU_Config.h"

class xml
{
    public:
        xml();
        virtual ~xml();

        void update(int i , uint8_t val);
        uint8_t read(int i);
    protected:
    private:
};

extern xml xmlfile;

#endif // XML_H
