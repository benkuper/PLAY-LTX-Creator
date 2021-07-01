/*
  ==============================================================================

    PatternClipUI.h
    Created: 30 Jun 2021 2:00:44pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "../PatternClip.h"

class PatternClipUI :
    public LayerBlockUI
{
public:
    PatternClipUI(PatternClip* clip);
    ~PatternClipUI();

    Image img;

    bool colorMode;
    Colour color;

    PatternClip* clip;

    void updatePattern();

    void paint(Graphics& g) override;
    void resizedBlockInternal() override;


    void controllableFeedbackUpdateInternal(Controllable* c) override;
};