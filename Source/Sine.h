/*
  ==============================================================================

    Sine.h
    Created: 11 Feb 2021 5:05:55pm
    Author:  Zeno  Loesch

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class Sine
{
public:
    Sine();
    ~Sine();
    double Sines
    (
    double frequency,
    float depth  
    );
    double preparetoPlay(double sampleRate);
private: 
    
    float mSmoothDepth;
    float phase;
    float dcoffset;
    float upperLimit = 1.0f, lowerLimit = 0.f;
    double freqinc;
    double m_sampleRate;
    float hann;
    float* output;
    float* input;
};
