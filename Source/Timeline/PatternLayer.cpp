/*
  ==============================================================================

    PatternLayer.cpp
    Created: 30 Jun 2021 2:01:26pm
    Author:  bkupe

  ==============================================================================
*/

#include "PatternLayer.h"
#include "PatternClip.h"
#include "ui/PatternLayerPanel.h"
#include "ui/PatternLayerTimeline.h"

PatternLayer::PatternLayer(Sequence * sequence, var params) :
    SequenceLayer(sequence, getTypeString()),
    clipManager(this)
{
    saveAndLoadRecursiveData = true;
    addChildControllableContainer(&clipManager);
}

PatternLayer::~PatternLayer()
{
}

SequenceLayerPanel* PatternLayer::getPanel()
{
    return new PatternLayerPanel(this);
}

SequenceLayerTimeline* PatternLayer::getTimelineUI()
{
    return new PatternLayerTimeline(this);
}

PatternClipManager::PatternClipManager(PatternLayer* layer) :
    LayerBlockManager(layer, "Patterns"),
    patternLayer(layer)
{
    blocksCanOverlap = false;
}

LayerBlock* PatternClipManager::createItem()
{
    return new PatternClip();
}
