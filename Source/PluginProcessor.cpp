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
initDSP();
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
                                                                   juce::NormalisableRange<float>(1.0f, 2.0f),
                                                                         1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat> (ParameterID[3],
                                                                     ParameterID[3],
                                                                      juce::NormalisableRange<float>(1.0f, 10.0f),
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
  params.push_back (std::make_unique<juce::AudioParameterFloat> (ParameterID[6],
                                                                 ParameterID[6],
                                                                 juce::NormalisableRange<float>(0.0f, 1.0f),
                                                                 1.0f));
                                                                  
                                                                  
    return {params.begin(), params.end()};
}
void AMSNYCAudioProcessor::initDSP()
{
    for (int i = 0; i < 2; i++)
    {
       // mSine[i] = std::make_unique<Sine>();
        mAR[i] = std::make_unique<AR>();
        mSineBuffer4[i] = std::make_unique<SineBuffer4>();
    }
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
    for (int i = 0; i < 2; ++i)
    {
        //mSine[i]->preparetoPlay(sampleRate);
        mSineBuffer4[i]->prepareSampleRate(sampleRate);
        mSineBuffer4[i]->phaseoffset(*treeState.getRawParameterValue(ParameterID[Parameter_Phase]));
       // mSineBuffer4[i]->inphase(0);
    }
    SampleRate = sampleRate;
    
}

void AMSNYCAudioProcessor::releaseResources()
{
    
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
        auto* channelDataLeft = buffer.getWritePointer(0);
        auto* channelDataRight = buffer.getWritePointer(1);

   
        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            playhead = this->getPlayHead();
             playhead->getCurrentPosition(hostInfo);
            
            auto frequencyinterpolationL = bpm_to_herz(hostInfo.bpm, *treeState.getRawParameterValue(ParameterID[Parameter_TimeSignatureLeft]));
               auto frequencyinterpolationR = bpm_to_herz(hostInfo.bpm, *treeState.getRawParameterValue(ParameterID[Parameter_TimeSignatureRight]));
                  m_frequency = linear_interp(frequencyinterpolationL, frequencyinterpolationR, *treeState.getRawParameterValue(ParameterID[Parameter_Interpolation]));
                 if (hostInfo.isPlaying == false)
                 {
                      mAR[channel]->gate(false);
                    
                     
                     if (mAR[channel]->getOutput()== 0.0f)
                     {
                   
                         mAR[channel]->reset();
                         mAR[channel]->setAttackRate(*treeState.getRawParameterValue(ParameterID[Parameter_Attack]) * SampleRate);
                         mAR[channel]->setReleaseRate(*treeState.getRawParameterValue(ParameterID[Parameter_Release]) * SampleRate);
                         
                         mSineBuffer4[channel]->setphaseL();
                         mSineBuffer4[channel]->setphaseR();
                         
                         mSineBuffer4[channel]->phaseoffset(*treeState.getRawParameterValue(ParameterID[Parameter_Phase]));
                         mSineBuffer4[channel]->inphase(1);
                           }
                 } else if (hostInfo.isPlaying == true )
                 {
           
                     mAR[channel]->gate(true);
                 }
                     
                const float resultLeft =
                channelDataLeft[sample]
                * mSineBuffer4[channel]->sinebuf4(m_frequency,*treeState.getRawParameterValue(ParameterID[Parameter_Depth]))* mAR[channel]->process();
                channelDataLeft[sample] = resultLeft;
            
                const float resultRight =
                channelDataRight[sample]
                * mSineBuffer4[channel]->sinbuf4R(m_frequency,*treeState.getRawParameterValue(ParameterID[Parameter_Depth])) * mAR[channel]->process();
                channelDataRight[sample] = resultRight;
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
int AMSNYCAudioProcessor::envelopestate(int channel)
{
    return mAR[channel]->getState();
}
