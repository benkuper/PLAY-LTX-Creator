/*
  ==============================================================================

    PatternClip.cpp
    Created: 30 Jun 2021 3:00:46pm
    Author:  bkupe

  ==============================================================================
*/

#include "PatternClip.h"
#include "Library/Library.h"

PatternClip::PatternClip() :
    LayerBlock(getTypeString()),
    pattern(nullptr)
{
    patternTarget = addTargetParameter("Pattern", "The pattern to use for this clip", Library::getInstance());
    patternTarget->targetType = TargetParameter::CONTAINER;
    patternTarget->maxDefaultSearchLevel = 0;
}

PatternClip::~PatternClip()
{
}

void PatternClip::setPattern(Pattern* p)
{
    if (p == pattern) return;
    if (pattern != nullptr)
    {
       // pattern->removeInspectableListener(this);
    }

    pattern = p;

    if (pattern != nullptr)
    {
       // pattern->addInspectableListener(this);
    }
}

void PatternClip::onContainerParameterChangedInternal(Parameter* p)
{
    LayerBlock::onContainerParameterChangedInternal(p);
    if (p == patternTarget) setPattern(dynamic_cast<Pattern*>(patternTarget->targetContainer.get()));
}

void PatternClip::inspectableDestroyed(Inspectable* i)
{
    if (i == pattern) setPattern(nullptr);
}
