/*
  ==============================================================================

    PatternClipUI.cpp
    Created: 30 Jun 2021 2:00:44pm
    Author:  bkupe

  ==============================================================================
*/

#include "PatternClipUI.h"
#include "Library/ColorPattern.h"
#include "Library/PicturePattern.h"

PatternClipUI::PatternClipUI(PatternClip* clip) :
    LayerBlockUI(clip),
    clip(clip)
{
    updatePattern();
}

PatternClipUI::~PatternClipUI()
{
}

void PatternClipUI::updatePattern()
{
    if (clip->pattern == nullptr)
    {
        colorMode = false;
        img = Image();
        repaint();
        return;
    }

    if (PicturePattern* pp = dynamic_cast<PicturePattern*>(clip->pattern))
    {
        colorMode = false;
        Image targetImage;
        if (pp->file->getFile().existsAsFile())
        {
            targetImage = ImageCache::getFromFile(pp->file->getFile());
        }

        if (targetImage.isValid()) img = targetImage.rescaled(jmax(getWidth(), 100), jmax(getHeight(), 100));
        else img = Image();
    }
    else if (ColorPattern* cp = dynamic_cast<ColorPattern*>(clip->pattern))
    {
        colorMode = true;
        color = cp->color->getColor();
    }

    repaint();
}

void PatternClipUI::paint(Graphics& g)
{
    LayerBlockUI::paint(g);

    if (colorMode)
    {
        g.setColour(color);
        g.fillRoundedRectangle(getLocalBounds().reduced(1).toFloat(), 2);
    }
    else
    {
        if (img.isValid())
        {
            g.setColour(Colours::white);
            g.drawImage(img, getLocalBounds().reduced(1).toFloat());
        }
    }
}

void PatternClipUI::resizedBlockInternal()
{

}

void PatternClipUI::controllableFeedbackUpdateInternal(Controllable* c)
{
    LayerBlockUI::controllableFeedbackUpdateInternal(c);
    if (c == clip->patternTarget) updatePattern();
}
