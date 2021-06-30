/*
  ==============================================================================

    LTXSequenceManager.h
    Created: 30 Jun 2021 2:26:40pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "LTXSequence.h"

class LTXSequenceManager :
    public SequenceManager
{
public:
    juce_DeclareSingleton(LTXSequenceManager,true);

    LTXSequenceManager();
    ~LTXSequenceManager();

    Sequence* createItem() override;
};