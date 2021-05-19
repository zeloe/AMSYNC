/*
  ==============================================================================

    PushButton.h
    Created: 19 Apr 2021 11:40:48pm
    Author:  Zeno  Loesch

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "PluginProcessor.h"
class PushButton :public  juce::Component, juce::Timer

{
public:
    PushButton(AMSNYCAudioProcessor* inProcessor);
    ~PushButton();
    void paint(juce::Graphics& g) override;
    void timerCallback() override;
    void getEnvelopeState(int instateL, int instateR);
  
private:
    AMSNYCAudioProcessor* mProcessor;
    int state;
    int stateL;
    int stateR;
     
    juce::Image PushButtonOff;
    juce::Image PushButtonOn;
  
};
