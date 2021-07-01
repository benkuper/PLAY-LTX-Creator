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

        FileParameter* fp = ((FileParameter*)clip->patternParams.getParameterByName(pp->file->shortName));
        if (fp->getFile().existsAsFile())
        {
            targetImage = ImageCache::getFromFile(fp->getFile());
        }

        if (targetImage.isValid()) img = targetImage.rescaled(jmax(getWidth(), 100), jmax(getHeight(), 100));
        else img = Image();
    }
    else if (ColorPattern* cp = dynamic_cast<ColorPattern*>(clip->pattern))
    {
        colorMode = true;
        color = ((ColorParameter *)clip->patternParams.getParameterByName(cp->color->shortName))->getColor();
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
        if (img.isValid() && clip->pattern != nullptr)
        {
            LayerBlockManagerUI* mui = (LayerBlockManagerUI*)getParentComponent();

            PicturePattern* pp = (PicturePattern*)clip->pattern;
            g.setColour(Colours::white);
            int repeatsH = clip->patternParams.getParameterByName(pp->horizontalRepetitions->shortName)->intValue();
            int repeatsV = clip->patternParams.getParameterByName(pp->verticalRepetitions->shortName)->intValue();

            int x1s = mui->timeline->getXForTime(1) - mui->timeline->getXForTime(0);
            int tw = jlimit<int>(1,8000, x1s / repeatsH);
            int th = jlimit<int>(1,8000,getHeight() / repeatsV);
            g.setTiledImageFill(img.rescaled(tw, th), 0, 0, 1);
            g.fillRoundedRectangle(getLocalBounds().reduced(1).toFloat(), 2);
            //g.drawImage(img, getLocalBounds().reduced(1).toFloat(),RectanglePlacement::);
        }
    }
}

void PatternClipUI::resizedBlockInternal()
{

}

void PatternClipUI::controllableFeedbackUpdateInternal(Controllable* c)
{
    LayerBlockUI::controllableFeedbackUpdateInternal(c);
    if (c == clip->patternTarget || c->parentContainer == &clip->patternParams) updatePattern();
}
