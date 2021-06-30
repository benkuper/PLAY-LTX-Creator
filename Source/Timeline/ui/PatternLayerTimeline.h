/*
  ==============================================================================

    PatternLayerTimeline.h
    Created: 30 Jun 2021 2:01:11pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once
#include "../PatternLayer.h"

class PatternLayerTimeline;

class PatternClipManagerUI :
    public LayerBlockManagerUI
{
public:
    PatternClipManagerUI(PatternLayerTimeline* timeline);
    ~PatternClipManagerUI();

    PatternClipManager* clipManager;
    PatternLayerTimeline* patternTimeline;

    int dropClipX;

    void paint(Graphics& g) override;

    LayerBlockUI* createUIForItem(LayerBlock* item) override;

    void itemDragEnter(const SourceDetails& source) override;
    void itemDragExit(const SourceDetails& source) override;
    void itemDragMove(const SourceDetails& source) override;
    void itemDropped(const SourceDetails& source) override;
};

class PatternLayerTimeline :
    public SequenceLayerTimeline
{
public:
    PatternLayerTimeline(PatternLayer* layer);
    ~PatternLayerTimeline();

    PatternLayer* patternLayer;
    
    PatternClipManagerUI clipManagerUI;

    void resized() override;
    void updateContent() override;
};