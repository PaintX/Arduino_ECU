/*
Speeduino - Simple engine management for the Arduino Mega 2560 platform
Copyright (C) Josh Stewart
A full copy of the license may be found in the projects root directory
*/

/*
This file contains the various crank and cam wheel decoder functions.

Each decoder must have the following 4 functions (Where xxxx is the decoder name):

* triggerSetup_xxx - Called once from within setup() and configures any required variables
* triggerPri_xxxx - Called each time the primary (No. 1) crank/cam signal is triggered (Called as an interrupt, so variables must be declared volatile)
* triggerSec_xxxx - Called each time the secondary (No. 2) crank/cam signal is triggered (Called as an interrupt, so variables must be declared volatile)
* getRPM_xxxx - Returns the current RPM, as calculated by the decoder
* getCrankAngle_xxxx - Returns the current crank angle, as calculated b the decoder

And each decoder must utlise at least the following variables:
toothLastToothTime - The time (In uS) that the last primary tooth was 'seen'
* 

*/

inline void addToothLogEntry(unsigned long time)
{
  //High speed tooth logging history
  toothHistory[toothHistoryIndex] = time;
  if(toothHistoryIndex == (TOOTH_LOG_BUFFER-1))
  { toothHistoryIndex = 0; BIT_CLEAR(currentStatus.squirt, BIT_SQUIRT_TOOTHLOG1READY); } //The tooth log ready bit is cleared to ensure that we only get a set of concurrent values. 
  else
  { toothHistoryIndex++; }
}

/*
As nearly all the decoders use a common method of determining RPM (The time the last full revolution took)
A common function is simpler
*/
inline int stdGetRPM()
{
  noInterrupts();
  revolutionTime = (toothOneTime - toothOneMinusOneTime); //The time in uS that one revolution would take at current speed (The time tooth 1 was last seen, minus the time it was seen prior to that)
  interrupts(); 
  return (US_IN_MINUTE / revolutionTime); //Calc RPM based on last full revolution time (Faster as /)
}

/*
This is a special case of RPM measure that is based on the time between the last 2 teeth rather than the time of the last full revolution
This gives much more volatile reading, but is quite useful during cranking, particularly on low resolution patterns.
It can only be used on patterns where the teeth are evently spaced
It takes an argument of the full (COMPLETE) number of teeth per revolution. For a missing tooth wheel, this is the number if the tooth had NOT been missing (Eg 36-1 = 36)
*/
inline int crankingGetRPM(byte totalTeeth)
{
  noInterrupts();
  revolutionTime = (toothLastToothTime - toothLastMinusOneToothTime) * totalTeeth;
  interrupts(); 
  return (US_IN_MINUTE / revolutionTime);
}

/* 
Name: Missing tooth wheel
Desc: A multi-tooth wheel with one of more 'missing' teeth. The first tooth after the missing one is considered number 1 and isthe basis for the trigger angle
Note: This does not currently support dual wheel (ie missing tooth + single tooth on cam)
*/
void triggerSetup_missingTooth()
{
  triggerToothAngle = 360 / configPage2.triggerTeeth; //The number of degrees that passes from tooth to tooth
  triggerActualTeeth = configPage2.triggerTeeth - configPage2.triggerMissingTeeth; //The number of physical teeth on the wheel. Doing this here saves us a calculation each time in the interrupt
  triggerFilterTime = (int)(1000000 / (MAX_RPM / 60 * configPage2.triggerTeeth)); //Trigger filter time is the shortest possible time (in uS) that there can be between crank teeth (ie at max RPM). Any pulses that occur faster than this time will be disgarded as noise
  secondDerivEnabled = false;
}

void triggerPri_missingTooth()
{
   // http://www.msextra.com/forums/viewtopic.php?f=94&t=22976
   // http://www.megamanual.com/ms2/wheel.htm

   curTime = micros();
   curGap = curTime - toothLastToothTime;
   if ( curGap < triggerFilterTime ) { return; } //Debounce check. Pulses should never be less than triggerFilterTime, so if they are it means a false trigger. (A 36-1 wheel at 8000pm will have triggers approx. every 200uS)
   toothCurrentCount++; //Increment the tooth counter
   
   addToothLogEntry(curGap);
   
   //Begin the missing tooth detection
   //If the time between the current tooth and the last is greater than 1.5x the time between the last tooth and the tooth before that, we make the assertion that we must be at the first tooth after the gap
   //if ( (curTime - toothLastToothTime) > (1.5 * (toothLastToothTime - toothLastMinusOneToothTime))) { toothCurrentCount = 1; }
   if(configPage2.triggerMissingTeeth == 1) { targetGap = (3 * (toothLastToothTime - toothLastMinusOneToothTime)) >> 1; } //Multiply by 1.5 (Checks for a gap 1.5x greater than the last one) (Uses bitshift to multiply by 3 then divide by 2. Much faster than multiplying by 1.5)
   //else { targetGap = (10 * (toothLastToothTime - toothLastMinusOneToothTime)) >> 2; } //Multiply by 2.5 (Checks for a gap 2.5x greater than the last one)
   else { targetGap = ((toothLastToothTime - toothLastMinusOneToothTime)) * 2; } //Multiply by 2 (Checks for a gap 2x greater than the last one)
   if ( curGap > targetGap || toothCurrentCount > triggerActualTeeth)
   { 
     toothCurrentCount = 1; 
     toothOneMinusOneTime = toothOneTime;
     toothOneTime = curTime;
     currentStatus.hasSync = true;
     startRevolutions++; //Counter 
   } 
   
   toothLastMinusOneToothTime = toothLastToothTime;
   toothLastToothTime = curTime;
}

void triggerSec_missingTooth(){ return; } //This function currently is not used

int getRPM_missingTooth()
{
   return stdGetRPM();
}

int getCrankAngle_missingTooth(int timePerDegree)
{
    //This is the current angle ATDC the engine is at. This is the last known position based on what tooth was last 'seen'. It is only accurate to the resolution of the trigger wheel (Eg 36-1 is 10 degrees)
    unsigned long tempToothLastToothTime;
    int tempToothCurrentCount;
    //Grab some variables that are used in the trigger code and assign them to temp variables. 
    noInterrupts();
    tempToothCurrentCount = toothCurrentCount;
    tempToothLastToothTime = toothLastToothTime;
    interrupts();
    
    int crankAngle = (tempToothCurrentCount - 1) * triggerToothAngle + configPage2.triggerAngle; //Number of teeth that have passed since tooth 1, multiplied by the angle each tooth represents, plus the angle that tooth 1 is ATDC. This gives accuracy only to the nearest tooth.
    //Estimate the number of degrees travelled since the last tooth}
    long elapsedTime = micros() - tempToothLastToothTime;
    if(elapsedTime < SHRT_MAX ) { crankAngle += div((int)elapsedTime, timePerDegree).quot; } //This option is much faster, but only available for smaller values of elapsedTime
    else { crankAngle += ldiv(elapsedTime, timePerDegree).quot; }

    if (crankAngle >= 720) { crankAngle -= 720; } 
    else if (crankAngle > 360) { crankAngle -= 360; }
    if (crankAngle < 0) { crankAngle += 360; }
    
    return crankAngle;
}

/* 
Name: Dual wheel
Desc: 2 wheels located either both on the crank or with the primary on the crank and the secondary on the cam. 
Note: There can be no missing teeth on the primary wheel
*/
void triggerSetup_DualWheel()
{
  triggerToothAngle = 360 / configPage2.triggerTeeth; //The number of degrees that passes from tooth to tooth
  toothCurrentCount = 255; //Default value
  triggerFilterTime = (int)(1000000 / (MAX_RPM / 60 * configPage2.triggerTeeth)); //Trigger filter time is the shortest possible time (in uS) that there can be between crank teeth (ie at max RPM). Any pulses that occur faster than this time will be disgarded as noise
  triggerSecFilterTime = (int)(1000000 / (MAX_RPM / 60 * 2)) / 2; //Same as above, but fixed at 2 teeth on the secondary input and divided by 2 (for cam speed)
  secondDerivEnabled = false;
}


void triggerPri_DualWheel()
{ 
   curTime = micros();
   curGap = curTime - toothLastToothTime;
   if ( curGap < triggerFilterTime ) { return; } //Debounce check. Pulses should never be less than triggerFilterTime, so if they are it means a false trigger. (A 36-1 wheel at 8000pm will have triggers approx. every 200uS)
   toothCurrentCount++; //Increment the tooth counter
   addToothLogEntry(curGap);
   if ( !currentStatus.hasSync ) { return; }
   
   if ( toothCurrentCount == 1 || toothCurrentCount > configPage2.triggerTeeth )
   { 
     toothCurrentCount = 1; 
     toothOneMinusOneTime = toothOneTime;
     toothOneTime = curTime;
     startRevolutions++; //Counter
     //if ((startRevolutions & 63) == 1) { currentStatus.hasSync = false; } //Every 64 revolutions, force a resync with the cam
   } 
   
   toothLastMinusOneToothTime = toothLastToothTime;
   toothLastToothTime = curTime;
}

void triggerSec_DualWheel()
{ 
  curTime2 = micros();
  curGap2 = curTime2 - toothLastSecToothTime;
  if ( curGap2 < triggerSecFilterTime ) { return; } 
  toothLastSecToothTime = curTime2;
  
  if(!currentStatus.hasSync)
  {
    toothCurrentCount = 0;
    currentStatus.hasSync = true;
  }
} 

int getRPM_DualWheel()
{
   return stdGetRPM();
}

int getCrankAngle_DualWheel(int timePerDegree)
{
    //This is the current angle ATDC the engine is at. This is the last known position based on what tooth was last 'seen'. It is only accurate to the resolution of the trigger wheel (Eg 36-1 is 10 degrees)
    unsigned long tempToothLastToothTime;
    int tempToothCurrentCount;
    //Grab some variables that are used in the trigger code and assign them to temp variables. 
    noInterrupts();
    tempToothCurrentCount = toothCurrentCount;
    tempToothLastToothTime = toothLastToothTime;
    interrupts();
    
    //Handle case where the secondary tooth was the last one seen
    if(tempToothCurrentCount == 0) { tempToothCurrentCount = configPage2.triggerTeeth; }
    
    int crankAngle = (tempToothCurrentCount - 1) * triggerToothAngle + configPage2.triggerAngle; //Number of teeth that have passed since tooth 1, multiplied by the angle each tooth represents, plus the angle that tooth 1 is ATDC. This gives accuracy only to the nearest tooth.
    //Estimate the number of degrees travelled since the last tooth}
    long elapsedTime = micros() - tempToothLastToothTime;
    if(elapsedTime < SHRT_MAX ) { crankAngle += div((int)elapsedTime, timePerDegree).quot; } //This option is much faster, but only available for smaller values of elapsedTime
    else { crankAngle += ldiv(elapsedTime, timePerDegree).quot; }
    
    
    if (crankAngle >= 720) { crankAngle -= 720; } 
    if (crankAngle > 360) { crankAngle -= 360; }
    if (crankAngle < 0) { crankAngle += 360; }
    
    return crankAngle;
}


/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Name: Basic Distributor
Desc: Tooth equal to the number of cylinders are evenly spaced on the cam. No position sensing (Distributor is retained) so crank angle is a made up figure based purely on the first teeth to be seen
Note: This is a very simple decoder. See http://www.megamanual.com/ms2/GM_7pinHEI.htm
*/
void triggerSetup_BasicDistributor()
{
  triggerActualTeeth = configPage1.nCylinders / 2;
  if(triggerActualTeeth == 0) { triggerActualTeeth = 1; }
  triggerToothAngle = 360 / triggerActualTeeth; //The number of degrees that passes from tooth to tooth
  triggerFilterTime = 60000000L / MAX_RPM / configPage1.nCylinders; // Minimum time required between teeth
  triggerFilterTime = triggerFilterTime / 2; //Safety margin
  secondDerivEnabled = false;
}

void triggerPri_BasicDistributor()
{
  curTime = micros();
  curGap = curTime - toothLastToothTime;
  if ( curGap < triggerFilterTime ) { return; } //Debounce check. Pulses should never be less than triggerFilterTime
  
  if(toothCurrentCount == triggerActualTeeth ) //Check if we're back to the beginning of a revolution
  { 
     toothCurrentCount = 1; //Reset the counter
     toothOneMinusOneTime = toothOneTime;
     toothOneTime = curTime;
     currentStatus.hasSync = true;
     startRevolutions++; //Counter 
  }
  else { toothCurrentCount++; } //Increment the tooth counter 
  
  addToothLogEntry(curGap);
  
  toothLastMinusOneToothTime = toothLastToothTime;
  toothLastToothTime = curTime;
}
void triggerSec_BasicDistributor() { return; } //Not required
int getRPM_BasicDistributor()
{
  if(currentStatus.RPM < configPage2.crankRPM) { return crankingGetRPM(triggerActualTeeth); }
  else { return stdGetRPM(); }
}
int getCrankAngle_BasicDistributor(int timePerDegree)
{
    //This is the current angle ATDC the engine is at. This is the last known position based on what tooth was last 'seen'. It is only accurate to the resolution of the trigger wheel (Eg 36-1 is 10 degrees)
    unsigned long tempToothLastToothTime;
    int tempToothCurrentCount;
    //Grab some variables that are used in the trigger code and assign them to temp variables. 
    noInterrupts();
    tempToothCurrentCount = toothCurrentCount;
    tempToothLastToothTime = toothLastToothTime;
    interrupts();
    
    //int crankAngle = (tempToothCurrentCount - 1) * triggerToothAngle + configPage2.triggerAngle; //Number of teeth that have passed since tooth 1, multiplied by the angle each tooth represents, plus the angle that tooth 1 is ATDC. This gives accuracy only to the nearest tooth.
    //crankAngle += ldiv( (micros() - tempToothLastToothTime), timePerDegree).quot; //Estimate the number of degrees travelled since the last tooth
   
    
    int crankAngle = (tempToothCurrentCount - 1) * triggerToothAngle + configPage2.triggerAngle; //Number of teeth that have passed since tooth 1, multiplied by the angle each tooth represents, plus the angle that tooth 1 is ATDC. This gives accuracy only to the nearest tooth.
    //Estimate the number of degrees travelled since the last tooth}
    long elapsedTime = micros() - tempToothLastToothTime;
    if(elapsedTime < SHRT_MAX ) { crankAngle += div((int)elapsedTime, timePerDegree).quot; } //This option is much faster, but only available for smaller values of elapsedTime
    else { crankAngle += ldiv(elapsedTime, timePerDegree).quot; }
    
    if (crankAngle >= 720) { crankAngle -= 720; } 
    if (crankAngle > 360) { crankAngle -= 360; }
    if (crankAngle < 0) { crankAngle += 360; }
    
    return crankAngle;
}

/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Name: GM7X
Desc: GM 7X trigger wheel. It has six equally spaced teeth and a seventh tooth for cylinder identification.
Note: Within the code below, the sync tooth is referred to as tooth #3 rather than tooth #7. This makes for simpler angle calculations
*/
void triggerSetup_GM7X()
{
  triggerToothAngle = 360 / 6; //The number of degrees that passes from tooth to tooth
  secondDerivEnabled = false;
}

void triggerPri_GM7X()
{
   lastGap = curGap;
   curTime = micros();
   curGap = curTime - toothLastToothTime;
   toothCurrentCount++; //Increment the tooth counter
   
   addToothLogEntry(curGap);
   
   //
   if( toothCurrentCount > 7 )
   {
     toothCurrentCount = 1; 
     toothOneMinusOneTime = toothOneTime; 
     toothOneTime = curTime;
   }
   else
   {
     targetGap = (lastGap) >> 1; //The target gap is set at half the last tooth gap
     if ( curGap < targetGap) //If the gap between this tooth and the last one is less than half of the previous gap, then we are very likely at the magical 3rd tooth
     { 
       toothCurrentCount = 3; 
       currentStatus.hasSync = true;
       startRevolutions++; //Counter 
       return; //We return here so that the tooth times below don't get set (The magical 3rd tooth should not be considered for any calculations that use those times)
     } 
   }
   
   toothLastMinusOneToothTime = toothLastToothTime;
   toothLastToothTime = curTime;
}
void triggerSec_GM7X() { return; } //Not required
int getRPM_GM7X()
{
   return stdGetRPM();
}
int getCrankAngle_GM7X(int timePerDegree)
{
    //This is the current angle ATDC the engine is at. This is the last known position based on what tooth was last 'seen'. It is only accurate to the resolution of the trigger wheel (Eg 36-1 is 10 degrees)
    unsigned long tempToothLastToothTime;
    int tempToothCurrentCount;
    //Grab some variables that are used in the trigger code and assign them to temp variables. 
    noInterrupts();
    tempToothCurrentCount = toothCurrentCount;
    tempToothLastToothTime = toothLastToothTime;
    interrupts();
    
    //Check if the last tooth seen was the reference tooth (Number 3). All others can be calculated, but tooth 3 has a unique angle
    int crankAngle;
    if( tempToothCurrentCount < 3 )
    {
      crankAngle = (tempToothCurrentCount - 1) * triggerToothAngle + 42; //Number of teeth that have passed since tooth 1, multiplied by the angle each tooth represents, plus the angle that tooth 1 is ATDC. This gives accuracy only to the nearest tooth.
    }
    else if( tempToothCurrentCount == 3 )
    {
      crankAngle = 112;
    }
    else
    {
      crankAngle = (tempToothCurrentCount - 2) * triggerToothAngle + 42; //Number of teeth that have passed since tooth 1, multiplied by the angle each tooth represents, plus the angle that tooth 1 is ATDC. This gives accuracy only to the nearest tooth.
    }
    
    //Estimate the number of degrees travelled since the last tooth}
    long elapsedTime = micros() - tempToothLastToothTime;
    if(elapsedTime < SHRT_MAX ) { crankAngle += div((int)elapsedTime, timePerDegree).quot; } //This option is much faster, but only available for smaller values of elapsedTime
    else { crankAngle += ldiv(elapsedTime, timePerDegree).quot; }
    
    if (crankAngle > 360) { crankAngle -= 360; }
    
    return crankAngle;
}


/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Name: Mitsubishi 4G63 / NA/NB Miata + MX-5 / 4/2
Desc: TBA
Note: https://raw.githubusercontent.com/noisymime/speeduino/master/reference/wiki/decoders/4g63_trace.png
Tooth #1 is defined as the next crank tooth after the crank signal is HIGH when the cam signal is falling.
Tooth number one is at 355* ATDC
*/
void triggerSetup_4G63()
{
  triggerToothAngle = 180; //The number of degrees that passes from tooth to tooth (primary)
  toothCurrentCount = 99; //Fake tooth count represents no sync
  secondDerivEnabled = false;
  
  //Note that these angles are for every rising and falling edge
  
  toothAngles[0] = 355; //Falling edge of tooth #1
  toothAngles[1] = 105; //Rising edge of tooth #2
  toothAngles[2] = 175; //Falling edge of tooth #2
  toothAngles[3] = 285; //Rising edge of tooth #1
  
  triggerFilterTime = 1500; //10000 rpm, assuming we're triggering on both edges off the crank tooth. 
  triggerSecFilterTime = (int)(1000000 / (MAX_RPM / 60 * 2)) / 2; //Same as above, but fixed at 2 teeth on the secondary input and divided by 2 (for cam speed)
}

void triggerPri_4G63()
{
  curTime = micros();
  curGap = curTime - toothLastToothTime;
  if ( curGap < triggerFilterTime ) { return; } //Debounce check. Pulses should never be less than triggerFilterTime
  
  toothCurrentCount++;
  if(toothCurrentCount == 1 || toothCurrentCount == 5) //Trigger is on CHANGE, hence 4 pulses = 1 crank rev
  { 
     toothCurrentCount = 1; //Reset the counter
     toothOneMinusOneTime = toothOneTime;
     toothOneTime = curTime;
     currentStatus.hasSync = true;
     startRevolutions++; //Counter
     //if ((startRevolutions & 15) == 1) { currentStatus.hasSync = false; } //Every 64 revolutions, force a resync with the cam
  }
  else if (!currentStatus.hasSync) { return; }
  
  addToothLogEntry(curGap);
   
  //Whilst this is an uneven tooth pattern, if the specific angle between the last 2 teeth is specified, 1st deriv prediction can be used
  if(toothCurrentCount == 1 || toothCurrentCount == 3) { triggerToothAngle = 70; triggerFilterTime = curGap; } //Trigger filter is set to whatever time it took to do 70 degrees (Next trigger is 110 degrees away)
  else { triggerToothAngle = 110; triggerFilterTime = (curGap * 3) >> 3; } //Trigger filter is set to (110*3)/8=41.25=41 degrees (Next trigger is 70 degrees away).
  
  curGap = curGap >> 1;
  
  toothLastMinusOneToothTime = toothLastToothTime;
  toothLastToothTime = curTime;
}
void triggerSec_4G63()
{ 
  curTime2 = micros();
  curGap2 = curTime2 - toothLastSecToothTime;
  if ( curGap2 < triggerSecFilterTime ) { return; } 
  toothLastSecToothTime = curTime2;
  
  if(BIT_CHECK(currentStatus.engine, BIT_ENGINE_CRANK) || !currentStatus.hasSync)
  {
    triggerFilterTime = 1500;
    //Check the status of the crank trigger
    bool crank = digitalRead(pinTrigger);
    if(crank == HIGH)
    {
      //triggerFilterTime = 1; //Effectively turns off the trigger filter for now 
      toothCurrentCount = 4; //If the crank trigger is currently HIGH, it means we're on tooth #1
    } 
  }
  //else { triggerFilterTime = 1500; } //reset filter time (ugly)
  return; 
}


int getRPM_4G63()
{
  //During cranking, RPM is calculated 4 times per revolution, once for each rising/falling of the crank signal. 
  //Because these signals aren't even (Alternating 110 and 70 degrees), this needs a special function
  if(currentStatus.RPM < configPage2.crankRPM) 
  { 
    int tempToothAngle;
    noInterrupts();
    tempToothAngle = triggerToothAngle;
    revolutionTime = (toothLastToothTime - toothLastMinusOneToothTime); //Note that trigger tooth angle changes between 70 and 110 depending on the last tooth that was seen  
    interrupts();
    revolutionTime = revolutionTime * 36;
    return (tempToothAngle * 60000000L) / revolutionTime;
  }
  else { return stdGetRPM(); }
}

int getCrankAngle_4G63(int timePerDegree)
{
    if(!currentStatus.hasSync) { return 0;}
    //This is the current angle ATDC the engine is at. This is the last known position based on what tooth was last 'seen'. It is only accurate to the resolution of the trigger wheel (Eg 36-1 is 10 degrees)
    unsigned long tempToothLastToothTime;
    int tempToothCurrentCount;
    //Grab some variables that are used in the trigger code and assign them to temp variables. 
    noInterrupts();
    tempToothCurrentCount = toothCurrentCount;
    tempToothLastToothTime = toothLastToothTime;
    interrupts();
    
    int crankAngle = toothAngles[(tempToothCurrentCount - 1)] + configPage2.triggerAngle; //Perform a lookup of the fixed toothAngles array to find what the angle of the last tooth passed was. 
    //Estimate the number of degrees travelled since the last tooth}
    
    long elapsedTime = micros() - tempToothLastToothTime;
    if(elapsedTime < SHRT_MAX ) { crankAngle += div((int)elapsedTime, timePerDegree).quot; } //This option is much faster, but only available for smaller values of elapsedTime
    else { crankAngle += ldiv(elapsedTime, timePerDegree).quot; }
    
    if (crankAngle >= 720) { crankAngle -= 720; }  
    if (crankAngle > 360) { crankAngle -= 360; }
    if (crankAngle < 0) { crankAngle += 360; }
    
    return crankAngle;
}

/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Name: GM 24X
Desc: TBA
Note: Useful references:
http://www.vems.hu/wiki/index.php?page=MembersPage%2FJorgenKarlsson%2FTwentyFourX
Provided that the cam signal is used, this decoder simply counts the teeth and then looks their angles up against a lookup table. The cam signal is used to determine tooth #1
*/
void triggerSetup_24X()
{
  triggerToothAngle = 15; //The number of degrees that passes from tooth to tooth (primary)
  toothAngles[0] = 12;
  toothAngles[1] = 18;
  toothAngles[2] = 33;
  toothAngles[3] = 48;
  toothAngles[4] = 63;
  toothAngles[5] = 78;
  toothAngles[6] = 102;
  toothAngles[7] = 108;
  toothAngles[8] = 123;
  toothAngles[9] = 138;
  toothAngles[10] = 162;
  toothAngles[11] = 177;
  toothAngles[12] = 183;
  toothAngles[13] = 198;
  toothAngles[14] = 222;
  toothAngles[15] = 237;
  toothAngles[16] = 252;
  toothAngles[17] = 258;
  toothAngles[18] = 282;
  toothAngles[19] = 288;
  toothAngles[20] = 312;
  toothAngles[21] = 327;
  toothAngles[22] = 342;
  toothAngles[23] = 357;
  
  toothCurrentCount = 25; //We set the initial tooth value to be something that should never be reached. This indicates no sync
  secondDerivEnabled = false;
}

void triggerPri_24X()
{
  if(toothCurrentCount == 25) { currentStatus.hasSync = false; return; } //Indicates sync has not been achieved (Still waiting for 1 revolution of the crank to take place)
  curTime = micros();
  curGap = curTime - toothLastToothTime;
  
  if(toothCurrentCount == 0)
  { 
     toothCurrentCount = 1; //Reset the counter
     toothOneMinusOneTime = toothOneTime;
     toothOneTime = curTime;
     currentStatus.hasSync = true;
     startRevolutions++; //Counter 
  }
  else
  {
    toothCurrentCount++; //Increment the tooth counter
  }
  
   addToothLogEntry(curGap);
   
   toothLastToothTime = curTime;
}
void triggerSec_24X()
{ 
  toothCurrentCount = 0; //All we need to do is reset the tooth count back to zero, indicating that we're at the beginning of a new revolution
  return; 
}

int getRPM_24X()
{
   return stdGetRPM();
}
int getCrankAngle_24X(int timePerDegree)
{
    //This is the current angle ATDC the engine is at. This is the last known position based on what tooth was last 'seen'. It is only accurate to the resolution of the trigger wheel (Eg 36-1 is 10 degrees)
    unsigned long tempToothLastToothTime;
    int tempToothCurrentCount;
    //Grab some variables that are used in the trigger code and assign them to temp variables. 
    noInterrupts();
    tempToothCurrentCount = toothCurrentCount;
    tempToothLastToothTime = toothLastToothTime;
    interrupts();
    
    int crankAngle;
    if (toothCurrentCount == 0) { crankAngle = 0 + configPage2.triggerAngle; } //This is the special case to handle when the 'last tooth' seen was the cam tooth. 0 is the angle at which the crank tooth goes high (Within 360 degrees). 
    else { crankAngle = toothAngles[(tempToothCurrentCount - 1)] + configPage2.triggerAngle;} //Perform a lookup of the fixed toothAngles array to find what the angle of the last tooth passed was. 
    
    //Estimate the number of degrees travelled since the last tooth}
    long elapsedTime = micros() - tempToothLastToothTime;
    if(elapsedTime < SHRT_MAX ) { crankAngle += div((int)elapsedTime, timePerDegree).quot; } //This option is much faster, but only available for smaller values of elapsedTime
    else { crankAngle += ldiv(elapsedTime, timePerDegree).quot; }
    
    
    if (crankAngle > 360) { crankAngle -= 360; }
    
    return crankAngle;
}

/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Name: Jeep 2000
Desc: For '91 to 2000 6 cylinder Jeep engines
Note: Quite similar to the 24X setup. 24 crank teeth over 720 degrees, in groups of 4. Crank wheel is high for 360 crank degrees. AS we only need timing within 360 degrees, only 12 tooth angles are defined.
Tooth number 1 represents the first tooth seen after the cam signal goes high
http://speeduino.com/forum/download/file.php?id=205
*/
void triggerSetup_Jeep2000()
{
  triggerToothAngle = 0; //The number of degrees that passes from tooth to tooth (primary)
  toothAngles[0] = 174;
  toothAngles[1] = 194;
  toothAngles[2] = 214;
  toothAngles[3] = 234;
  toothAngles[4] = 294;
  toothAngles[5] = 314;
  toothAngles[6] = 334;
  toothAngles[7] = 354;
  toothAngles[8] = 414;
  toothAngles[9] = 434;
  toothAngles[10] = 454;
  toothAngles[11] = 474;
  
  toothCurrentCount = 13; //We set the initial tooth value to be something that should never be reached. This indicates no sync
  secondDerivEnabled = false;
}

void triggerPri_Jeep2000()
{
  if(toothCurrentCount == 13) { currentStatus.hasSync = false; return; } //Indicates sync has not been achieved (Still waiting for 1 revolution of the crank to take place)
  curTime = micros();
  curGap = curTime - toothLastToothTime;
  
  if(toothCurrentCount == 0)
  { 
     toothCurrentCount = 1; //Reset the counter
     toothOneMinusOneTime = toothOneTime;
     toothOneTime = curTime;
     currentStatus.hasSync = true;
     startRevolutions++; //Counter 
  }
  else
  {
    toothCurrentCount++; //Increment the tooth counter
  }
  
  addToothLogEntry(curGap);
   
  toothLastMinusOneToothTime = toothLastToothTime;
  toothLastToothTime = curTime;
}
void triggerSec_Jeep2000()
{ 
  toothCurrentCount = 0; //All we need to do is reset the tooth count back to zero, indicating that we're at the beginning of a new revolution
  return; 
}

int getRPM_Jeep2000()
{
   return stdGetRPM();
}
int getCrankAngle_Jeep2000(int timePerDegree)
{
    //This is the current angle ATDC the engine is at. This is the last known position based on what tooth was last 'seen'. It is only accurate to the resolution of the trigger wheel (Eg 36-1 is 10 degrees)
    unsigned long tempToothLastToothTime;
    int tempToothCurrentCount;
    //Grab some variables that are used in the trigger code and assign them to temp variables. 
    noInterrupts();
    tempToothCurrentCount = toothCurrentCount;
    tempToothLastToothTime = toothLastToothTime;
    interrupts();
    
    int crankAngle;
    if (toothCurrentCount == 0) { crankAngle = 146 + configPage2.triggerAngle; } //This is the special case to handle when the 'last tooth' seen was the cam tooth. 146 is the angle at which the crank tooth goes high. 
    else { crankAngle = toothAngles[(tempToothCurrentCount - 1)] + configPage2.triggerAngle;} //Perform a lookup of the fixed toothAngles array to find what the angle of the last tooth passed was. 
    //Estimate the number of degrees travelled since the last tooth}
    long elapsedTime = micros() - tempToothLastToothTime;
    if(elapsedTime < SHRT_MAX ) { crankAngle += div((int)elapsedTime, timePerDegree).quot; } //This option is much faster, but only available for smaller values of elapsedTime
    else { crankAngle += ldiv(elapsedTime, timePerDegree).quot; }
    
    
    if (crankAngle > 360) { crankAngle -= 360; }
    
    return crankAngle;
}

/* 
Name: Audi 135
Desc: 135 teeth on the crank and 1 tooth on the cam. 
Note: This is very similar to the dual wheel decoder, however due to the 135 teeth not dividing evenly into 360, only every 3rd crank tooth is used in calculating the crank angle. This effectively makes it a 45 tooth dual wheel setup
*/
void triggerSetup_Audi135()
{
  triggerToothAngle = 8; //135/3 = 45, 360/45 = 8 degrees every 3 teeth
  toothCurrentCount = 255; //Default value
  toothSystemCount = 0;
  triggerFilterTime = (unsigned long)(1000000 / (MAX_RPM / 60 * 135UL)); //Trigger filter time is the shortest possible time (in uS) that there can be between crank teeth (ie at max RPM). Any pulses that occur faster than this time will be disgarded as noise
  triggerSecFilterTime = (int)(1000000 / (MAX_RPM / 60 * 2)) / 2; //Same as above, but fixed at 2 teeth on the secondary input and divided by 2 (for cam speed)
  secondDerivEnabled = false;
}

void triggerPri_Audi135()
{ 
   curTime = micros();
   curGap = curTime - toothSystemLastToothTime;
   if ( curGap < triggerFilterTime ) { return; }
   toothSystemCount++;
   toothSystemLastToothTime = curTime;
   addToothLogEntry(curGap);
   if ( !currentStatus.hasSync ) { return; }
   if ( toothSystemCount < 3 ) { return; } //We only proceed for every third tooth
   
   toothSystemCount = 0;
   toothCurrentCount++; //Increment the tooth counter
   
   if ( toothCurrentCount == 1 || toothCurrentCount > 45 )
   { 
     toothCurrentCount = 1;
     toothOneMinusOneTime = toothOneTime;
     toothOneTime = curTime;
     startRevolutions++; //Counter
   } 
   
   toothLastMinusOneToothTime = toothLastToothTime;
   toothLastToothTime = curTime;
}

void triggerSec_Audi135()
{ 
  curTime2 = micros();
  curGap2 = curTime2 - toothLastSecToothTime;
  if ( curGap2 < triggerSecFilterTime ) { return; } 
  toothLastSecToothTime = curTime2;
  
  if( !currentStatus.hasSync )
  {
    toothCurrentCount = 0;
    currentStatus.hasSync = true;
    toothSystemCount = 3; //Need to set this to 3 so that the next primary tooth is counted
  }
} 

int getRPM_Audi135()
{
   return stdGetRPM();
}

int getCrankAngle_Audi135(int timePerDegree)
{   
        //This is the current angle ATDC the engine is at. This is the last known position based on what tooth was last 'seen'. It is only accurate to the resolution of the trigger wheel (Eg 36-1 is 10 degrees)
    unsigned long tempToothLastToothTime;
    int tempToothCurrentCount;
    //Grab some variables that are used in the trigger code and assign them to temp variables. 
    noInterrupts();
    tempToothCurrentCount = toothCurrentCount;
    tempToothLastToothTime = toothLastToothTime;
    interrupts();
    
    //Handle case where the secondary tooth was the last one seen
    if(tempToothCurrentCount == 0) { tempToothCurrentCount = 45; }
    
    int crankAngle = (tempToothCurrentCount - 1) * triggerToothAngle + configPage2.triggerAngle; //Number of teeth that have passed since tooth 1, multiplied by the angle each tooth represents, plus the angle that tooth 1 is ATDC. This gives accuracy only to the nearest tooth.
    //Estimate the number of degrees travelled since the last tooth}
    long elapsedTime = micros() - tempToothLastToothTime;
    if(elapsedTime < SHRT_MAX ) { crankAngle += div((int)elapsedTime, timePerDegree).quot; } //This option is much faster, but only available for smaller values of elapsedTime
    else { crankAngle += ldiv(elapsedTime, timePerDegree).quot; }
    
    
    if (crankAngle >= 720) { crankAngle -= 720; } 
    if (crankAngle > 360) { crankAngle -= 360; }
    if (crankAngle < 0) { crankAngle += 360; }
    
    return crankAngle;
}

