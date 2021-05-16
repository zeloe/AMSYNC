/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "Parameters.h"
//==============================================================================
AMSNYCAudioProcessorEditor::AMSNYCAudioProcessorEditor (AMSNYCAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
     setSize(500, 500);
   mInterface = std::make_unique<Interface>();
 
   setLookAndFeel(mInterface.get());
  
    Interface::setDefaultLookAndFeel(mInterface.get());
    addAndMakeVisible (DepthSlider);
    DepthSlider.setRange(0.0, 1.0);
    DepthSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    sliderValueDepth = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState,ParameterID[0],DepthSlider);
     
    addAndMakeVisible(DepthLabel);
    DepthLabel.setText("Depth", juce::dontSendNotification);
    DepthLabel.attachToComponent (&DepthSlider, true);

    addAndMakeVisible(InterpolationSlider);
    InterpolationSlider.setRange(0.0, 1.0);
    InterpolationSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    InterpolationSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 0, 0);
    sliderValueInterpolation = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState,ParameterID[1],InterpolationSlider);
   
    addAndMakeVisible(InterpolationLabel);
    InterpolationLabel.setText("Interpolation", juce::dontSendNotification);

    InterpolationLabel.attachToComponent(&InterpolationSlider, true);
        
    addAndMakeVisible(AttackSlider);
    AttackSlider.setRange(0.001,10);
    AttackSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    sliderValueAttack = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState,ParameterID[2],AttackSlider);
  
    
    addAndMakeVisible(AttackLabel);
    AttackLabel.setText("Attack", juce::dontSendNotification);
    AttackLabel.attachToComponent(&AttackSlider, true);
    
    addAndMakeVisible(ReleaseSlider);
    ReleaseSlider.setRange(0.001,30);
    ReleaseSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    sliderValueRelease = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState,ParameterID[3],ReleaseSlider);
     
    
    addAndMakeVisible(ReleaseLabel);
    ReleaseLabel.setText("Release", juce::dontSendNotification);
    ReleaseLabel.attachToComponent(&ReleaseSlider, true);
    
    addAndMakeVisible(PhaseSlider);
    PhaseSlider.setRange(0.0f,1.0f);
    PhaseSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    sliderValuePhase = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState,ParameterID[6],PhaseSlider);
    
    addAndMakeVisible(PhaseLabel);
    PhaseLabel.setText("Phase", juce::dontSendNotification);
    PhaseLabel.attachToComponent(&PhaseSlider, true);
    
    
        addAndMakeVisible(ComboBoxLeft);
        ComboBoxLeft.addItem("1/1",1);
        ComboBoxLeft.addItem("1/2",2);
        ComboBoxLeft.addItem("1/4",3);
        ComboBoxLeft.addItem("1/8",4);
        ComboBoxLeft.addItem("1/16",5);
        ComboBoxLeft.addItem("1/32",6);
        ComboBoxLeft.addItem("1/64",7);
        ComboBoxLeft.addItem("Free",8);
    
        comboBoxLeft = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState,ParameterID[4],ComboBoxLeft);
   
    
        addAndMakeVisible(ComboBoxRight);
        ComboBoxRight.addItem("1/1 ",1);
        ComboBoxRight.addItem("1/2 ",2);
        ComboBoxRight.addItem("1/4 ",3);
        ComboBoxRight.addItem("1/8 ",4);
        ComboBoxRight.addItem("1/16 ",5);
        ComboBoxRight.addItem("1/32 ",6);
        ComboBoxRight.addItem("1/64 ",7);
        ComboBoxRight.addItem("Free",8);
         
        comboBoxRight = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.treeState,ParameterID[5],ComboBoxRight);
    mBackgroundImage = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    mPushButton = std::make_unique<PushButton>(&audioProcessor);
    mPushButton->getEnvelopeState(audioProcessor.envelopestate(0), audioProcessor.envelopestate(1));
    mPushButton->setBounds(80+90*2.5+10,90* 3,100,100);
    addAndMakeVisible(mPushButton.get());
   
}

AMSNYCAudioProcessorEditor::~AMSNYCAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
    Interface::setDefaultLookAndFeel(nullptr);
}

//==============================================================================
void AMSNYCAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.drawImage(mBackgroundImage,getLocalBounds().toFloat());
   // g.setColour (juce::Colours::black);
}

void AMSNYCAudioProcessorEditor::resized()
{
    const int sliderLeft = 80;
    const int dimension = 150;
    const int offset = 90;
    DepthSlider.setBounds(sliderLeft, 0, dimension, dimension);
    InterpolationSlider.setBounds(sliderLeft+ offset, offset+60,dimension + 100, dimension /2);
    
    ComboBoxLeft.setBounds(10 + offset, offset + 30 , 100, 20);
    ComboBoxRight.setBounds(sliderLeft + offset * 2.5 +10  , offset + 30 , 100, 20);
     
    AttackSlider.setBounds(sliderLeft,offset * 2 + 20, dimension, dimension);
    ReleaseSlider.setBounds(sliderLeft, offset * 3 + 20, dimension, dimension);
    PhaseSlider.setBounds(sliderLeft,offset * 4 + 20,dimension,dimension);
}
