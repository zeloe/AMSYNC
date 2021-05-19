/*
  ==============================================================================

    Sine_Buffer.h
    Created: 17 Apr 2021 1:30:03am
    Author:  Zeno  Loesch

  ==============================================================================
*/

#pragma once
#include "DSP_Helper.h"
#include "math.h"


class SineBuffer4
{
public:
    SineBuffer4();
    ~SineBuffer4();
    
    double sinebuf4 (
                     double frequency,
                     float depth
                     );
    double sinbuf4R (
                     double frequency,
                     float depth
                     );
    void prepareSampleRate(double sampleRate);
    void phaseoffset(double offset);
    void inphase(double inphase);
    void setphaseL ();
    void setphaseR ();
private:
    double m_sampleRate;
    float mSmoothDepth;
    float dcoffset;
    double phase;
    double phaseL;
    float frequencysmooth;
    double m_phaseoffset;
    double temp;
    double tempL;
};
