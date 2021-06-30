/*
  ==============================================================================

    Pattern.cpp
    Created: 30 Jun 2021 1:59:34pm
    Author:  bkupe

  ==============================================================================
*/

#include "Pattern.h"
#include "ui/PatternUI.h"

Pattern::Pattern(const String& name, var params) :
    BaseItem(name, false)
{
    itemDataType = "Pattern";
}

Pattern::~Pattern()
{
}

PatternUI* Pattern::createUI()
{
    return new PatternUI(this);
}
