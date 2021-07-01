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
    file = patternParams.addFileParameter("Picture", "Picture to use for this pattern");

    horizontalRepetitions = patternParams.addIntParameter("Horizontal Repetitions", "Number of horizontal repetitions of the picture", 1, 1);
    verticalRepetitions = patternParams.addIntParameter("Vertical Repetitions", "Number of vertical repetitions of the picture", 1, 1);
    mirrorV = patternParams.addBoolParameter("Vertical Mirror", "If the picture should be mirrored vertically when looping", false);
}

PicturePattern::~PicturePattern()
{
}

PatternUI* PicturePattern::createUI()
{
    return new PicturePatternUI(this);
}
