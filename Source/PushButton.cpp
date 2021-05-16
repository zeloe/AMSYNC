/*
  ==============================================================================

    PushButton.cpp
    Created: 19 Apr 2021 11:40:48pm
    Author:  Zeno  Loesch

  ==============================================================================
*/

#include "PushButton.h"
PushButton::PushButton(AMSNYCAudioProcessor* inProcessor)
: mProcessor(inProcessor), stateL(-1),stateR(-1)
   {
        PushButtonOff = juce::ImageCache::getFromMemory(BinaryData::push_button_normal_png, BinaryData::push_button_normal_pngSize);
        PushButtonOn = juce::ImageCache::getFromMemory(BinaryData::push_button_pressed_png, BinaryData::push_button_pressed_pngSize);
   }
   PushButton::~PushButton()
   {
       
   }
   void PushButton::paint(juce::Graphics& g)
   {
       
       if (mProcessor->envelopestate(0) == 0 || mProcessor->envelopestate(0) == 0)
       {
            
        g.drawImage(PushButtonOff,(getLocalBounds()).toFloat(),juce::RectanglePlacement::stretchToFit);
       } else if (mProcessor->envelopestate(0) > 0 || mProcessor->envelopestate(1) > 0)
       {
           
        g.drawImage(PushButtonOn,(getLocalBounds()).toFloat(),juce::RectanglePlacement::stretchToFit);
       } else {
           
       }
   }

void PushButton::timerCallback()
{
    
    if (stateL == 0 && stateR == 0)
    {
     
       stopTimer();
    } else if (stateL > 0 && stateR > 0)
    {
        
        repaint();
        stopTimer();
    } else {
        repaint();
    }
    
}
void PushButton::getEnvelopeState(int instateL, int instateR)
{
    stateL = instateL;
    stateR = instateR;
    startTimerHz(15);
}
