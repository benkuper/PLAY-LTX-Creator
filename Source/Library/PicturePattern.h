/*
  ==============================================================================

    PicturePattern.h
    Created: 30 Jun 2021 1:59:43pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "Pattern.h"

class PicturePattern :
    public Pattern
{
public:
    PicturePattern(var params = var());
    ~PicturePattern();

    virtual String getTypeString() const override { return "Picture"; }
};