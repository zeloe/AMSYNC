/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//#include "Sine.h"

#include "AR.h"

#include "Sine_Buffer.h"
//==============================================================================
/**
*/
class AMSNYCAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    AMSNYCAudioProcessor();
    ~AMSNYCAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    juce::AudioProcessorValueTreeState treeState;
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    int envelopestate (int channel);
        double phase;
private:
    juce::AudioPlayHead* playhead;
    juce::AudioPlayHead::CurrentPositionInfo hostInfo;
    void initDSP();
    double m_frequency;
    //static const int kChannels = 2;
    double SampleRate;
   // Sine sineprocess[kChannels];
   // std::unique_ptr<Sine> mSine[2];
    //AR *env = new AR();
    std::unique_ptr<AR> mAR[2];

    std::unique_ptr<SineBuffer4> mSineBuffer4[2];
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AMSNYCAudioProcessor)
};
