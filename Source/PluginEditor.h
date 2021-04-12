/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

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
    juce::Slider DepthSlider;
    juce::Slider InterpolationSlider;
    juce::Slider AttackSlider;
    juce::Slider ReleaseSlider;
     
    juce::Label DepthLabel;
    juce::Label InterpolationLabel;
    juce::Label AttackLabel;
    juce::Label ReleaseLabel;
    
    
    
    
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
     
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AMSNYCAudioProcessorEditor)
};
