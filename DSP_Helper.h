/*
  ==============================================================================

    DSP_Helper.h
    Created: 11 Feb 2021 5:28:42pm
    Author:  Zeno  Loesch

  ==============================================================================
*/

#pragma once

#define TWOPI 6.283185307179586476925286766559
inline float linear_interp(float const v0, float const v1, float const t )
{
    return (1 - t) * v0 + t * v1;
}


inline double bpm_to_herz (double const bpm, double const timesignatureindex)
{
    double result;
    if (timesignatureindex == 0)
    {
        result = 240;
        
    } else if (timesignatureindex == 1)
    {
        result = 120;
       
    } else if (timesignatureindex == 2)
    {
        result = 60;
  
    } else if (timesignatureindex == 3)
    {
        result = 30;
  
    } else if (timesignatureindex == 4)
    {
        result = 15;
   
    } else if (timesignatureindex == 5)
    {
        result = 7.5;
   
    } else if (timesignatureindex == 6)
    {
        result = 3.75;
     
    } else
    {
        return (1000.0f);
    }
       return (bpm / static_cast<double>(result));
}
