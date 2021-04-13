/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include "DSP_Helper.h"

#include "Parameters.h"
//==============================================================================
AMSNYCAudioProcessor::AMSNYCAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
treeState(*this,nullptr,"Parameter",{createParameterLayout()})
#endif
{
createParameterLayout();
}
juce::AudioProcessorValueTreeState::ParameterLayout AMSNYCAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>>  params;

    
    params.push_back (std::make_unique<juce::AudioParameterFloat> (ParameterID[0],
                                                                   ParameterID[0],
                                                                       juce::NormalisableRange<float>(0.0f, 1.0f),
                                                                       0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (ParameterID[1],
                                                                  ParameterID[1],
                                                                   juce::NormalisableRange<float>(0.0f, 1.0f),
                                                                         0.5f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (ParameterID[2],
                                                                  ParameterID[2],
                                                                   juce::NormalisableRange<float>(0.001f, 10.0f),
                                                                         1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (ParameterID[3],
                                                                     ParameterID[3],
                                                                      juce::NormalisableRange<float>(0.001f, 30.0f),
                                                                            1.0f));
   params.push_back (std::make_unique<juce::AudioParameterChoice>(ParameterID[4],
                                                                  ParameterID[4],
                                                                  TimeSignature,
                                                                 3
                                                                 ));
    params.push_back (std::make_unique<juce::AudioParameterChoice>(ParameterID[5],
                                                                   ParameterID[5],
                                                                   TimeSignature,
                                                                     2
                                                                   ));
  
                                                                  
                                                                  
    return {params.begin(), params.end()};
}
AMSNYCAudioProcessor::~AMSNYCAudioProcessor()
{
}

//==============================================================================
const juce::String AMSNYCAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AMSNYCAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AMSNYCAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AMSNYCAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AMSNYCAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AMSNYCAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AMSNYCAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AMSNYCAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AMSNYCAudioProcessor::getProgramName (int index)
{
    return {};
}

void AMSNYCAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AMSNYCAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    for (int i = 0; i < kChannels; i++){
        sineprocess[i].preparetoPlay(sampleRate);
    }
    SampleRate = sampleRate;
}

void AMSNYCAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AMSNYCAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AMSNYCAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

   
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

   
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);
        playhead = this->getPlayHead();
        playhead->getCurrentPosition(hostInfo);
        env->setAttackRate(*treeState.getRawParameterValue(ParameterID[Parameter_Attack]) * SampleRate);
        env->setReleaseRate(*treeState.getRawParameterValue(ParameterID[Parameter_Release]) * SampleRate);
         
            if (hostInfo.isPlaying == false)
            {
                env->gate(false);
                if (env->getState() == 1)
                {
                env->reset();
                }
            } else if (hostInfo.isPlaying == true)
            {
                env->gate(true);
            }
       
    auto frequencyinterpolationL = bpm_to_herz(hostInfo.bpm, *treeState.getRawParameterValue(ParameterID[Parameter_TimeSignatureLeft]));
    auto frequencyinterpolationR = bpm_to_herz(hostInfo.bpm, *treeState.getRawParameterValue(ParameterID[Parameter_TimeSignatureRight]));
       m_frequency = linear_interp(frequencyinterpolationL, frequencyinterpolationR, *treeState.getRawParameterValue(ParameterID[Parameter_Interpolation]));
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            const float resultar = channelData[sample] *   sineprocess[channel].Sines(m_frequency,*treeState.getRawParameterValue(ParameterID[Parameter_Depth])) * env->process();
            channelData[sample] = resultar;
        }
}
}

//==============================================================================
bool AMSNYCAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AMSNYCAudioProcessor::createEditor()
{
    return new AMSNYCAudioProcessorEditor (*this);
}

//==============================================================================
void AMSNYCAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
     auto state = treeState.copyState();
           std::unique_ptr<juce::XmlElement> xml (state.createXml());
           copyXmlToBinary (*xml, destData);
}

void AMSNYCAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
    
           if (xmlState.get() != nullptr)
               if (xmlState->hasTagName (treeState.state.getType()))
                   treeState.replaceState (juce::ValueTree::fromXml (*xmlState));
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AMSNYCAudioProcessor();
}
