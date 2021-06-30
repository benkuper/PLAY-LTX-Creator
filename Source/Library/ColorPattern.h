/*
  ==============================================================================

    ColorPattern.h
    Created: 30 Jun 2021 1:59:49pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "Pattern.h"

class ColorPattern :
    public Pattern
{
public:
    ColorPattern(var params = var());
    ~ColorPattern();

    virtual String getTypeString() const override { return "Color"; }
};