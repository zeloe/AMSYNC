/*
  ==============================================================================

    Sine_Buffer.cpp
    Created: 17 Apr 2021 1:30:03am
    Author:  Zeno  Loesch

  ==============================================================================
*/

#include "Sine_Buffer.h"
#include <iostream>
// algorithm from maximilian lib
SineBuffer4::SineBuffer4()
{
  phase = 0;
  phaseL = 0;
}
SineBuffer4::~SineBuffer4()
{
    
}
double SineBuffer4::sinebuf4(double frequency,
                            float depth
                             )
{
    double output;
     
    double remainder;
    
    frequencysmooth = frequencysmooth - 0.001f*(frequencysmooth-frequency);
    phase = phase * temp;
    phase += 512./(m_sampleRate/(frequencysmooth));
    if ( phase >= 511 )
    {
    phase -=512;
    }
    
    remainder = phase - floor(phase);
    output = (double) ((1-remainder) * sineBuffer[(1+ static_cast<long>(phase)) % 512] + remainder * sineBuffer[(2+static_cast<long>(phase)) % 512]);
    
     mSmoothDepth = mSmoothDepth - 0.001f*(mSmoothDepth-depth);
     dcoffset = 1.0f - mSmoothDepth;
    output = dcoffset + mSmoothDepth * (0.5*(1+output));
    return(output);
}


double SineBuffer4::sinbuf4R(double frequency,
                             float depth
                             )
{
    
  
    double output;
      
    double remainder;
   
    frequencysmooth = frequencysmooth - 0.001f*(frequencysmooth-frequency);
  
    
    phaseL += 512./(m_sampleRate/(frequencysmooth));
   
    
   
    if ( phaseL >= 511 )
    {
    phaseL -=512;
    }
    remainder = phaseL - floor(phaseL);
    output = (double) ((1-remainder) * sineBuffer[(1+static_cast<long>(phaseL)) % 512] + (remainder) * sineBuffer[(2+ static_cast<long>(phaseL)) % 512]);
 
    mSmoothDepth = mSmoothDepth - 0.001f*(mSmoothDepth-depth);
    dcoffset = 1.0f - mSmoothDepth;
       output = dcoffset + mSmoothDepth * (0.5*(1+output));
    return(output);
    
}

void SineBuffer4::prepareSampleRate(double sampleRate)
{
    m_sampleRate = sampleRate;
}

void SineBuffer4::phaseoffset(double offset)
{
    tempL = offset;
    if (tempL == 0)
      {
      tempL = 1.0f;
      tempL = tempL * 512.0f;
  phaseL = tempL * phaseL;
      } else {
        tempL = tempL * 512.0f;
        phaseL = tempL * phaseL;
      }
}
void SineBuffer4::inphase(double inphase)
{
    (temp = inphase);
}
void SineBuffer4::setphaseL()
{
    phase = 1.0f;
}
void SineBuffer4::setphaseR()
{
    phaseL = 1.0f;
}
