/*
  ==============================================================================

    Interface.h
    Created: 14 Apr 2021 7:18:32pm
    Author:  Zeno  Loesch

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "ColoursandFonts.h"

class Interface
:  public juce::LookAndFeel_V3
{
public:
    Interface()
    {
        //sliderimage
        
         mSliderWellImage = juce::ImageCache::getFromMemory(BinaryData::slider_well_png, BinaryData::slider_well_pngSize);
        mSliderThumbImage = juce::ImageCache::getFromMemory(BinaryData::slider_thumb_png, BinaryData::slider_thumb_pngSize);
        mSliderImage = juce::ImageCache::getFromMemory(BinaryData::large_knob_135frames_png, BinaryData::large_knob_135frames_pngSize);
        //combobox
         juce::LookAndFeel_V3::setColour(juce::ComboBox::backgroundColourId, Colour_3);
         juce::LookAndFeel_V3::setColour(juce::ComboBox::outlineColourId, Colour_2);
         juce::LookAndFeel_V3::setColour(juce::ComboBox::arrowColourId,Colour_1);
         juce::LookAndFeel_V3::setColour(juce::ComboBox::textColourId, Colour_1);
        
        //button
         juce::LookAndFeel_V3::setColour(juce::TextButton::buttonColourId, Colour_1);
         juce::LookAndFeel_V3::setColour(juce::TextButton::textColourOnId, Colour_1);
         juce::LookAndFeel_V3::setColour(juce::TextButton::textColourOffId, Colour_1);
    };
   virtual ~Interface()
    {
        
      };
//combobox
    
   juce::Font getLabelFont(juce::Label& label) override
   {
       return juce::Font("Helvetica Neue",12.00f, 1);
   }
    

   void drawPopupMenuItem (juce::Graphics& g, const juce::Rectangle<int>& area,
   bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu,
                           const juce::String& text, const juce::String& shortcutKeyText,
                           const juce::Drawable* icon, const juce::Colour* textColour) override
   {
       juce::Rectangle<int> r (area);
       
       juce::Colour fillColour =  isHighlighted ? Colour_5 : Colour_4;
       g.setColour(fillColour);
       
       g.fillRect(r.getX(),r.getY(),r.getWidth(),r.getHeight() -1);
       
       juce::Colour MyTextColour = isTicked ? Red : Colour_1;
       g.setColour(MyTextColour);
       g.setFont(juce::Font("Helvetica Neue",12.00f, 1));
       r.setLeft(10);
       r.setY(0);
       g.drawFittedText(text, r, juce::Justification::left, 1);
       
       
   }
   void drawComboBox (juce::Graphics& g, int width, int height, bool isButtonDown,
   int buttonX, int buttonY, int buttonW, int buttonH,
                      juce::ComboBox& box) override
   {
       const float cornerSize = 3.0f;
       const juce::Rectangle<int> boxBounds(0,0,width,height);
   
       g.setColour(Colour_7);
       g.fillRoundedRectangle(boxBounds.toFloat(),cornerSize);
       
       juce::Rectangle<int> arrow (width-30,0,20,height);
       juce::Path path;
       
       path.startNewSubPath(arrow.getX(), arrow.getCentreY() -2.f);
       path.lineTo(arrow.toFloat().getCentreX(), arrow.toFloat().getCentreY() -2.0f);
       path.lineTo(arrow.toFloat().getRight() -3.0f, arrow.toFloat().getCentreY() -2.0f);
       
       juce::Colour arrorColour = box.findColour(juce::ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 0.9f : 0.2f);
       g.setColour(arrorColour);
       g.strokePath(path, juce::PathStrokeType(2.0f));
   }
   
   //sliders
   void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
   float sliderPosProportional, float rotaryStartAngle,
                          float rotaryEndAngle, juce::Slider& slider) override
 
   {
       const int numFrames = mSliderImage.getHeight() / mSliderImage.getWidth();
       const int frameIndex = (int)std::ceil(sliderPosProportional * (numFrames - 1));
       
       const float radius = juce::jmin(width*0.5, height*0.5);
       const float centreX = x + width * 0.5f;
       const float centreY = y + height * 0.5f;
       const float rx = centreX - radius;
       const float ry = centreY - radius;
       g.drawImage(mSliderImage,
                   rx,
                   ry,
                   2*radius,
                   2*radius,
                   0,
                   frameIndex * mSliderImage.getWidth(),
                   mSliderImage.getWidth(),
                   mSliderImage.getWidth());
   }
    //label
    void drawLabel (juce::Graphics& g, juce::Label& label) override
    {
        g.fillAll (label.findColour (juce::Label::backgroundColourId));

        if (! label.isBeingEdited())
        {
            auto alpha = label.isEnabled() ? 1.0f : 0.5f;
            const juce::Font font (getLabelFont (label));

            g.setColour (Red);
            g.setFont (font);

            auto textArea = getLabelBorderSize (label).subtractedFrom (label.getLocalBounds());

            g.drawFittedText (label.getText(), textArea, label.getJustificationType(),
                              fmax (1, (int) ((float) textArea.getHeight() / font.getHeight())),
                              label.getMinimumHorizontalScale());

            g.setColour (label.findColour (juce::Label::outlineColourId).withMultipliedAlpha (alpha));
        }
        else if (label.isEnabled())
        {
            g.setColour (Red);
        }

        g.drawRect (label.getLocalBounds());
    }
   private:
       juce::Image mSliderImage;
       juce::Image mSliderWellImage;
    juce::Image mSliderThumbImage;
};
