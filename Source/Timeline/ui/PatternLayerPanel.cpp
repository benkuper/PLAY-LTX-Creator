/*
  ==============================================================================

    PatternLayerPanel.cpp
    Created: 30 Jun 2021 2:01:15pm
    Author:  bkupe

  ==============================================================================
*/

#include "PatternLayerPanel.h"

PatternLayerPanel::PatternLayerPanel(PatternLayer* layer) :
    SequenceLayerPanel(layer),
    patternLayer(layer)
{
}

PatternLayerPanel::~PatternLayerPanel()
{
}
