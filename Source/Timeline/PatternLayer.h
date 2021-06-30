/*
  ==============================================================================

    PatternLayer.h
    Created: 30 Jun 2021 2:01:26pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"

class PatternLayer;

class PatternClipManager :
    public LayerBlockManager
{
public:
    PatternClipManager(PatternLayer * layer);
    ~PatternClipManager() {}

    PatternLayer* patternLayer;

    LayerBlock* createItem() override;
};

class PatternLayer :
    public SequenceLayer
{
public:
    PatternLayer(Sequence * sequence, var params = var());
    ~PatternLayer();

    PatternClipManager clipManager;


    SequenceLayerPanel* getPanel() override;
    SequenceLayerTimeline* getTimelineUI() override;

    String getTypeString() const override { return "Patterns"; }
    static PatternLayer* create(Sequence* s, var params) { return new PatternLayer(s, params); }
};


