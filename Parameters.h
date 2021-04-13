/*
  ==============================================================================

    Parameters.h
    Created: 11 Apr 2021 6:57:52pm
    Author:  Zeno  Loesch

  ==============================================================================
*/

#pragma once
enum Parameter
{
    Parameter_Depth,
    Parameter_Interpolation,
    Parameter_Attack,
    Parameter_Release,
    Parameter_TimeSignatureLeft,
    Parameter_TimeSignatureRight,
   
    Parameter_TotalNumParameters
};

const juce::String ParameterID[Parameter_TotalNumParameters]
{
    "Depth",
    "Interpolation",
    "Attack",
    "Release",
    "Time Signature Left",
    "Time Signature Right"
};

const juce::StringArray TimeSignature
{
    "1/1",
    "1/2",
    "1/4",
    "1/8",
    "1/16",
    "1/32",
    "1/64",
    "Free"
};
