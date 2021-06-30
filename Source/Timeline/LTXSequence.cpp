/*
  ==============================================================================

    LTXSequence.cpp
    Created: 30 Jun 2021 2:25:42pm
    Author:  bkupe

  ==============================================================================
*/

#include "LTXSequence.h"
#include "PatternLayer.h"

LTXSequence::LTXSequence()
{
    layerFactory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Patterns", &PatternLayer::create, this));
    layerFactory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Audio", &AudioLayer::create, this));

}

LTXSequence::~LTXSequence()
{
}
