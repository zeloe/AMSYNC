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
class PushButton :public juce::Component
{
public:
    PushButton(AMSNYCAudioProcessor* inProcessor);
    ~PushButton();
    void paint(juce::Graphics& g) override;
    
    
   
private:
    AMSNYCAudioProcessor* mProcessor;
    int state;
    juce::Image PushButtonOff;
    juce::Image PushButtonOn;
    
};
