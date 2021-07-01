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
    pattern(nullptr),
    patternParams("Parameter Overrides")
{
    saveAndLoadRecursiveData = true;

    patternTarget = addTargetParameter("Pattern", "The pattern to use for this clip", Library::getInstance());
    patternTarget->targetType = TargetParameter::CONTAINER;
    patternTarget->maxDefaultSearchLevel = 0;

    addChildControllableContainer(&patternParams);
}

PatternClip::~PatternClip()
{
    setPattern(nullptr);
}

void PatternClip::setPattern(Pattern* p)
{
    if (p == pattern) return;
    if (pattern != nullptr)
    {
        pattern->removeInspectableListener(this);
        pattern->patternParams.removeControllableContainerListener(this);
    }

    pattern = p;

    if (pattern != nullptr)
    {
        pattern->addInspectableListener(this);
        pattern->patternParams.addControllableContainerListener(this);
    }

    setParamsFromPattern();
}

void PatternClip::setParamsFromPattern()
{
    patternParams.clear();

    if (pattern == nullptr) return;

    Array<WeakReference<Parameter>> params = pattern->patternParams.getAllParameters();
    for (auto& p : params)
    {
        Parameter* pp = ControllableFactory::createParameterFrom(p, true, true);
        patternParams.addParameter(pp);
    }
}

void PatternClip::onContainerParameterChangedInternal(Parameter* p)
{
    LayerBlock::onContainerParameterChangedInternal(p);
    if (p == patternTarget) setPattern(dynamic_cast<Pattern*>(patternTarget->targetContainer.get()));
}

void PatternClip::onControllableFeedbackUpdateInternal(ControllableContainer* cc, Controllable* c)
{
    LayerBlock::onControllableFeedbackUpdateInternal(cc, c);

    if (pattern != nullptr && cc == &pattern->patternParams)
    {
        if (Parameter* pp = patternParams.getParameterByName(c->shortName))
        {
            pp->defaultValue = ((Parameter *)c)->getValue();
            if (pp->controlMode == Parameter::MANUAL && !pp->isOverriden) pp->resetValue();
        }
    }
    

}

void PatternClip::inspectableDestroyed(Inspectable* i)
{
    if (i == pattern) setPattern(nullptr);
}