/*
  ==============================================================================

    PatternLayerPanel.h
    Created: 30 Jun 2021 2:01:15pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "../PatternLayer.h"

class PatternLayerPanel :
    public SequenceLayerPanel
{
public:
    PatternLayerPanel(PatternLayer* layer);
    ~PatternLayerPanel();

    PatternLayer* patternLayer;
};