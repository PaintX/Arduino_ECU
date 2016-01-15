#include "Advance_Table.h"


AdvanceTable::s_TABLE3D table;


/*
Populates a table with some reasonably realistic ignition advance data
*/
void dummyIgnitionTable()
{
    int tempXAxis[8] = {500,1500,2000,2500,3000,4000,5000,6000};
    for (uint8_t x = 0; x< table.xSize; x++) { table.axisX[x] = tempXAxis[x]; }
    //*myFuelTable->axisX = *tempXAxis;
    int tempYAxis[8] = {100,88,75,63,50,30,20,10};
    for (uint8_t x = 0; x< table.ySize; x++) { table.axisY[x] = tempYAxis[x]; }
    //*myFuelTable->axisY = *tempYAxis;

    //Go through the 8 rows and add the column values
    uint8_t tempRow1[8] = {10,15,20,26,35,40,43,44};
    uint8_t tempRow2[8] = {10,88,75,63,50,38,25,44};
    uint8_t tempRow3[8] = {12,88,75,63,50,38,25,40};
    uint8_t tempRow4[8] = {12,88,75,63,50,38,25,36};
    uint8_t tempRow5[8] = {28,88,75,63,50,38,25,13};
    uint8_t tempRow6[8] = {22,23,75,63,50,38,25,13};
    uint8_t tempRow7[8] = {17,21,75,63,50,38,25,13};
    uint8_t tempRow8[8] = {15,20,25,63,50,38,25,13};
    for (uint8_t x = 0; x< table.xSize; x++) { table.values[0][x] = tempRow1[x]; }
    for (uint8_t x = 0; x< table.xSize; x++) { table.values[1][x] = tempRow2[x]; }
    for (uint8_t x = 0; x< table.xSize; x++) { table.values[2][x] = tempRow3[x]; }
    for (uint8_t x = 0; x< table.xSize; x++) { table.values[3][x] = tempRow4[x]; }
    for (uint8_t x = 0; x< table.xSize; x++) { table.values[4][x] = tempRow5[x]; }
    for (uint8_t x = 0; x< table.xSize; x++) { table.values[5][x] = tempRow6[x]; }
    for (uint8_t x = 0; x< table.xSize; x++) { table.values[6][x] = tempRow7[x]; }
    for (uint8_t x = 0; x< table.xSize; x++) { table.values[7][x] = tempRow8[x]; }
}


//-- init
AdvanceTable::AdvanceTable()
{
    dummyIgnitionTable();
}




//This function pulls a value from a 3D table given a target for X and Y coordinates.
//It performs a 2D linear interpolation as descibred in: http://www.megamanual.com/v22manual/ve_tuner.pdf
int AdvanceTable::get3DTableValue(int Y, int X)
{

  #if 1
    //Loop through the X axis bins for the min/max pair
    //Note: For the X axis specifically, rather than looping from tableAxisX[0] up to tableAxisX[max], we start at tableAxisX[Max] and go down.
    // This is because the important tables (fuel and injection) will have the highest RPM at the top of the X axis, so starting there will mean the best case occurs when the RPM is highest (And hence the CPU is needed most)
    int xMinValue = table.axisX[0];
    int xMaxValue = table.axisX[table.xSize-1];
    int xMin = 0;
    int xMax = 0;

    //If the requested X value is greater/small than the maximum/minimum bin, reset X to be that value
    if(X > xMaxValue) { X = xMaxValue; }
    if(X < xMinValue) { X = xMinValue; }

    for (int x = table.xSize-1; x >= 0; x--)
    {
      //Checks the case where the X value is exactly what was requested
      if ( (X == table.axisX[x]) || (x == 0) )
      {
        xMaxValue = table.axisX[x];
        xMinValue = table.axisX[x];
        xMax = x;
        xMin = x;
        break;
      }
      //Normal case
      if ( (X <= table.axisX[x]) && (X > table.axisX[x-1]) )
      {
        xMaxValue = table.axisX[x];
        xMinValue = table.axisX[x-1];
        xMax = x;
        xMin = x-1;
        break;
      }
    }

    //Loop through the Y axis bins for the min/max pair
    int yMaxValue = table.axisY[0];
    int yMinValue = table.axisY[table.ySize-1];
    int yMin = 0;
    int yMax = 0;

    //If the requested Y value is greater/small than the maximum/minimum bin, reset Y to be that value
    if(Y > yMaxValue) { Y = yMaxValue; }
    if(Y < yMinValue) { Y = yMinValue; }

    for (int y = table.ySize-1; y >= 0; y--)
    {
      //Checks the case where the Y value is exactly what was requested
      if ( (Y == table.axisY[y]) || (y==0) )
      {
        yMaxValue = table.axisY[y];
        yMinValue = table.axisY[y];
        yMax = y;
        yMin = y;
        break;
      }
      //Normal case
      if ( (Y >= table.axisY[y]) && (Y < table.axisY[y-1]) )
      {
        yMaxValue = table.axisY[y];
        yMinValue = table.axisY[y-1];
        yMax = y;
        yMin = y-1;
        break;
      }
    }


    /*
At this point we have the 4 corners of the map where the interpolated value will fall in
Eg: (yMin,xMin) (yMin,xMax)
(yMax,xMin) (yMax,xMax)
In the following calculation the table values are referred to by the following variables:
A B
C D
*/
    int A = table.values[yMin][xMin];
    int B = table.values[yMin][xMax];
    int C = table.values[yMax][xMin];
    int D = table.values[yMax][xMax];

    //Create some normalised position values
    //These are essentially percentages (between 0 and 1) of where the desired value falls between the nearest bins on each axis

    // Float version
    /*
float p, q;
if (xMaxValue == xMinValue)
{ p = (float)(X-xMinValue); }
else { p = ((float)(X - xMinValue)) / (float)(xMaxValue - xMinValue); }
if (yMaxValue == yMinValue)
{ q = (float)(Y - yMinValue); }
else { q = ((float)(Y - yMaxValue)) / (float)(yMinValue - yMaxValue); }
float m = (1.0-p) * (1.0-q);
float n = p * (1-q);
float o = (1-p) * q;
float r = p * q;
return ( (A * m) + (B * n) + (C * o) + (D * r) );
*/

    // Non-Float version:
    //Initial check incase the values were hit straight on
    long p;
    if (xMaxValue == xMinValue)
    { p = ((long)(X - xMinValue) << 8); } //This only occurs if the requested X value was equal to one of the X axis bins
    else
    {
      p = ((long)(X - xMinValue) << 8) / (xMaxValue - xMinValue); //This is the standard case
    }

    long q;
    if (yMaxValue == yMinValue)
    { q = ((long)(Y - yMinValue) << 8); }
    else
    { q = ((long)(Y - yMaxValue) << 8) / (yMinValue - yMaxValue); }

    int m = ((257-p) * (257-q)) >> 8;
    int n = (p * (257-q)) >> 8;
    int o = ((257-p) * q) >> 8;
    int r = (p * q) >> 8;

    return ( (A * m) + (B * n) + (C * o) + (D * r) ) >> 8;

#else
return 0;
    #endif

  }
