/*
  ==============================================================================

    PatternLayer.cpp
    Created: 30 Jun 2021 2:01:26pm
    Author:  bkupe

  ==============================================================================
*/

#include "PatternLayer.h"

PatternLayer::PatternLayer(Sequence * sequence, var params) :
    SequenceLayer(sequence, getTypeString()),
    clipManager(this)
{
}

PatternLayer::~PatternLayer()
{
}

PatternClipManager::PatternClipManager(PatternLayer* layer) :
    LayerBlockManager(layer, "Patterns"),
    patternLayer(layer)
{
}
