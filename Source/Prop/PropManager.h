/*
  ==============================================================================

    PropManager.h
    Created: 30 Jun 2021 1:57:35pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "Prop.h"

class PropManager :
    public BaseManager<Prop>
{
public:
    juce_DeclareSingleton(PropManager, true)

    PropManager();
    ~PropManager();
};