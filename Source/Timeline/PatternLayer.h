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
class PatternClip;

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

    enum PropType { BALL, HOOP, PIXEL144, PIXEL64, PIXEL32, CUSTOM };
    IntParameter* numPixels;
    IntParameter* refreshRate;

    EnumParameter* propType;
    Trigger* exportToPRG;

    void onContainerParameterChangedInternal(Parameter* p) override;
    void onContainerTriggerTriggered(Trigger* t) override;

    void exportLayer();

    Array<PatternClip *> getValidClips();

    SequenceLayerPanel* getPanel() override;
    SequenceLayerTimeline* getTimelineUI() override;

    String getTypeString() const override { return "Patterns"; }
    static PatternLayer* create(Sequence* s, var params) { return new PatternLayer(s, params); }
};


