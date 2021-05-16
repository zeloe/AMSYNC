/*
  ==============================================================================

    PushButton.cpp
    Created: 19 Apr 2021 11:40:48pm
    Author:  Zeno  Loesch

  ==============================================================================
*/

#include "PushButton.h"
PushButton::PushButton(AMSNYCAudioProcessor* inProcessor)
: mProcessor(inProcessor), state (0)
   {
        PushButtonOff = juce::ImageCache::getFromMemory(BinaryData::push_button_normal_png, BinaryData::push_button_normal_pngSize);
        PushButtonOn = juce::ImageCache::getFromMemory(BinaryData::push_button_pressed_png, BinaryData::push_button_pressed_pngSize);
   }
   PushButton::~PushButton()
   {
       
   }
   void PushButton::paint(juce::Graphics& g)
   {
       
       if (mProcessor->envelopestate(0) == 0)
       {
           repaint();
        g.drawImage(PushButtonOff,(getLocalBounds()).toFloat(),juce::RectanglePlacement::stretchToFit);
       } else {
           repaint();
           g.drawImage(PushButtonOn,(getLocalBounds()).toFloat(),juce::RectanglePlacement::stretchToFit);
       }
   }
