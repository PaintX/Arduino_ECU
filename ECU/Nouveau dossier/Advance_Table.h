#ifndef _ADVANCE_TABLE_H_
#define _ADVANCE_TABLE_H_

#if defined(ARDUINO) && ARDUINO >= 100
   #include <Arduino.h>
#else
   #include <WProgram.h>
#endif

   class AdvanceTable
   {
      public:
       
        typedef struct {
          //All tables must be the same size for simplicity
          const static byte xSize = 8;
          const static byte ySize = 8;
          
          byte values[ySize][xSize];
          int axisX[xSize];
          int axisY[ySize];
          
        }s_TABLE3D;

        /*
        3D Tables have an origin (0,0) in the top left hand corner. Vertical axis is expressed first.
        Eg: 2x2 table
        -----
        |2 7|
        |1 4|
        -----
        (0,1) = 7
        (0,0) = 2
        (1,0) = 1
        */
      //****************************
      //  Configuration
      //****************************
      
         // constructor
        // AdvanceTable();
  
        int AdvanceTable::get3DTableValue(s_TABLE3D fromTable, int Y, int X);
   };
#endif

