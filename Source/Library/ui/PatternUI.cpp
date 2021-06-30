/*
  ==============================================================================

    PatternUI.cpp
    Created: 30 Jun 2021 2:00:13pm
    Author:  bkupe

  ==============================================================================
*/

#include "PatternUI.h"
#include "../PicturePattern.h"
#include "../ColorPattern.h"

PatternUI::PatternUI(Pattern* p) :
    BaseItemMinimalUI(p)
{
}

PatternUI::~PatternUI()
{
}


PicturePatternUI::PicturePatternUI(PicturePattern* pp) :
    PatternUI(pp),
    pp(pp)
{
    updatePattern();
}

void PicturePatternUI::updatePattern()
{
    Image targetImg;
    if (pp->file->getFile().existsAsFile())
    {
        targetImg = ImageCache::getFromFile(pp->file->getFile());
    }
    else
    {
        targetImg = ImageCache::getFromMemory(BinaryData::picture_png, BinaryData::picture_pngSize);
    }

    img = targetImg.rescaled(128, 128); //max thumb size
    repaint();
}

void PicturePatternUI::paint(Graphics& g)
{
    if (img.isValid())
    {
        g.setColour(Colours::white);
        g.drawImage(img, getLocalBounds().reduced(2).toFloat());
    }
}

void PicturePatternUI::controllableFeedbackUpdateInternal(Controllable* c)
{
    if (c == pp->file)
    {
        updatePattern();
    }
}



ColorPatternUI::ColorPatternUI(ColorPattern* cp) :
    PatternUI(cp),
    cp(cp)
{
}

void ColorPatternUI::paint(Graphics& g)
{
    g.setColour(cp->color->getColor());
    g.fillRoundedRectangle(getLocalBounds().reduced(2).toFloat(), 4);
}

void ColorPatternUI::controllableFeedbackUpdateInternal(Controllable* c)
{
    if (c == cp->color) repaint();
}
