/*
  ==============================================================================

    PicturePattern.cpp
    Created: 30 Jun 2021 1:59:43pm
    Author:  bkupe

  ==============================================================================
*/

#include "PicturePattern.h"
#include "ui/PatternUI.h"

PicturePattern::PicturePattern(var params) :
    Pattern(getTypeString(), params)
{
    file = addFileParameter("Picture", "Picture to use for this pattern");

}

PicturePattern::~PicturePattern()
{
}

PatternUI* PicturePattern::createUI()
{
    return new PicturePatternUI(this);
}
