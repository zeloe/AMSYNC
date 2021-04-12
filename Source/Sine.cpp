/*
  ==============================================================================

    Sine.cpp
    Created: 11 Feb 2021 5:05:55pm
    Author:  Zeno  Loesch

  ==============================================================================
*/



#include "Sine.h"

#include <cmath>

#include "DSP_Helper.h"


Sine::Sine()
{
}
Sine::~Sine()
{
}
double Sine::preparetoPlay(double sampleRate)
{
  return  m_sampleRate = sampleRate;
}
double Sine::Sines (
                      double frequency,
                      float depth
                        )
                   
{
   
        // algorithm from maximilian lib
        mSmoothDepth = mSmoothDepth - 0.001f*(mSmoothDepth-depth);
        dcoffset = 1.0f - mSmoothDepth;
        hann =  dcoffset + mSmoothDepth * (0.5f*(1.0f+std::cos(phase*static_cast<float>(TWOPI))));
        if (phase >= 1.0f ) {
            phase -= 1.0f;
        }
        phase += 1.0f/(m_sampleRate/(frequency));
        return hann;
}


