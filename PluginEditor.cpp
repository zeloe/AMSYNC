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
     setSize(800, 240);

    addAndMakeVisible (DepthSlider);
    DepthSlider.setRange(0.0, 1.0);
   
    sliderValueDepth = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState,ParameterID[0],DepthSlider);
     
    addAndMakeVisible(DepthLabel);
    DepthLabel.setText("Depth", juce::dontSendNotification);
    DepthLabel.attachToComponent (&DepthSlider, true);

    addAndMakeVisible(InterpolationSlider);
    InterpolationSlider.setRange(0.0, 1.0);
   
    sliderValueInterpolation = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState,ParameterID[1],InterpolationSlider);
   
    addAndMakeVisible(InterpolationLabel);
    InterpolationLabel.setText("Interpolation", juce::dontSendNotification);
    InterpolationLabel.attachToComponent(&InterpolationSlider, true);
        
    addAndMakeVisible(AttackSlider);
    AttackSlider.setRange(0.001,10);
   
    sliderValueAttack = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState,ParameterID[2],AttackSlider);
  
    
    addAndMakeVisible(AttackLabel);
    AttackLabel.setText("Attack", juce::dontSendNotification);
    AttackLabel.attachToComponent(&AttackSlider, true);
    
    addAndMakeVisible(ReleaseSlider);
    ReleaseSlider.setRange(0.001,30);
    sliderValueRelease = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.treeState,ParameterID[3],ReleaseSlider);
     
    
    addAndMakeVisible(ReleaseLabel);
    ReleaseLabel.setText("Release", juce::dontSendNotification);
    ReleaseLabel.attachToComponent(&ReleaseSlider, true);
    
    
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
    
}

AMSNYCAudioProcessorEditor::~AMSNYCAudioProcessorEditor()
{
}

//==============================================================================
void AMSNYCAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.setColour (juce::Colours::white);
}

void AMSNYCAudioProcessorEditor::resized()
{
     const int sliderLeft = 80;
    DepthSlider.setBounds(sliderLeft, 10, getWidth() - sliderLeft - 20, 20);
    InterpolationSlider.setBounds(sliderLeft, 80, getWidth() - sliderLeft - 20, 20);
    
    ComboBoxLeft.setBounds(sliderLeft,40, 100, 20);
    ComboBoxRight.setBounds(getWidth() - (sliderLeft + 50), 40, 100, 20);
     
    AttackSlider.setBounds(sliderLeft,110, getWidth() - sliderLeft - 20, 20);
    ReleaseSlider.setBounds(sliderLeft,140, getWidth() - sliderLeft - 20, 20);
    
}
