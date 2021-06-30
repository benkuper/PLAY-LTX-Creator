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

    void setPattern(Pattern* p);

    void onContainerParameterChangedInternal(Parameter* p) override;

    void inspectableDestroyed(Inspectable* i) override;

    String getTypeString() const override { return "Pattern Clip"; }
};