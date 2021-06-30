/*
  ==============================================================================

    Pattern.h
    Created: 30 Jun 2021 1:59:34pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class PatternUI;

class Pattern :
    public BaseItem
{
public:
    Pattern(const String &name = "Pattern", var params = var());
    virtual ~Pattern();


    virtual PatternUI* createUI();
};