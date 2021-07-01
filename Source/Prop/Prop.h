/*
  ==============================================================================

    Prop.h
    Created: 30 Jun 2021 1:57:38pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class Prop :
    public BaseItem
{
public:
    Prop(var params = var());
    virtual ~Prop();


    String getTypeString() const override { return "Prop"; }
};