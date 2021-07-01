/*
  ==============================================================================

    ColorPattern.cpp
    Created: 30 Jun 2021 1:59:49pm
    Author:  bkupe

  ==============================================================================
*/

#include "ColorPattern.h"
#include "ui/PatternUI.h"

ColorPattern::ColorPattern(var params) :
    Pattern(getTypeString(), params)
{
    color = patternParams.addColorParameter("Color", "Color for this pattern", BLUE_COLOR);
}

ColorPattern::~ColorPattern()
{
}

PatternUI* ColorPattern::createUI()
{
    return new ColorPatternUI(this);
}
