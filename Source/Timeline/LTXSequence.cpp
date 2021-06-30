/*
  ==============================================================================

    LTXSequence.cpp
    Created: 30 Jun 2021 2:25:42pm
    Author:  bkupe

  ==============================================================================
*/

#include "LTXSequence.h"
#include "PatternLayer.h"
#include "Audio/AudioManager.h"

LTXSequence::LTXSequence()
{
    layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Patterns", &PatternLayer::create, this));
    layerManager->factory.defs.add(SequenceLayerManager::LayerDefinition::createDef("", "Audio", &AudioLayer::create, this));

    setAudioDeviceManager(&AudioManager::getInstance()->am);
}

LTXSequence::~LTXSequence()
{
}
