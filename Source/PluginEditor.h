/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Interface.h"
#include "PushButton.h"
//==============================================================================
/**
*/
class AMSNYCAudioProcessorEditor  : public juce::AudioProcessorEditor
                                
{
public:
    AMSNYCAudioProcessorEditor (AMSNYCAudioProcessor&);
    ~AMSNYCAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
  
    
private:
    std::unique_ptr <Interface> mInterface;
    std::unique_ptr <PushButton> mPushButton;
   // std::unique_ptr <DrawSliderBackGround> mDrawSliderBackgroud;
    juce::Slider DepthSlider;
    juce::Slider InterpolationSlider;
    juce::Slider AttackSlider;
    juce::Slider ReleaseSlider;
    juce::Slider PhaseSlider;
    juce::Image mBackgroundImage;
    juce::Label DepthLabel;
    juce::Label InterpolationLabel;
    juce::Label AttackLabel;
    juce::Label ReleaseLabel;
    juce::Label PhaseLabel;
    
    
    juce::ComboBox ComboBoxLeft;
    juce::ComboBox ComboBoxRight;
  
    AMSNYCAudioProcessor& audioProcessor;
public:
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> sliderValueDepth;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> sliderValueInterpolation;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> comboBoxLeft;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> comboBoxRight;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> sliderValueAttack;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> sliderValueRelease;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> sliderValuePhase;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AMSNYCAudioProcessorEditor)
};
