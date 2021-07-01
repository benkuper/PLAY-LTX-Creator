/*
  ==============================================================================

    PatternClip.h
    Created: 30 Jun 2021 3:00:46pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "Library/Pattern.h"

class PatternClip :
    public LayerBlock,
    public Inspectable::InspectableListener
{
public:
    PatternClip();
    ~PatternClip();

    TargetParameter * patternTarget;
    Pattern* pattern;
    
    ControllableContainer patternParams;

    void setPattern(Pattern* p);

    void setParamsFromPattern();



    void inspectableDestroyed(Inspectable* i) override;

    void onContainerParameterChangedInternal(Parameter* p) override;
    void onControllableFeedbackUpdateInternal(ControllableContainer* cc, Controllable * c) override;

    String getTypeString() const override { return "Pattern Clip"; }

    //DECLARE_ASYNC_EVENT(PatternClip, PatternClip, patternClip, { PATTERN_UPDATED });
};