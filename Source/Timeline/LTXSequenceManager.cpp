/*
  ==============================================================================

    LTXSequenceManager.cpp
    Created: 30 Jun 2021 2:26:40pm
    Author:  bkupe

  ==============================================================================
*/

#include "LTXSequenceManager.h"

juce_ImplementSingleton(LTXSequenceManager)

LTXSequenceManager::LTXSequenceManager()
{
}

LTXSequenceManager::~LTXSequenceManager()
{
}

Sequence* LTXSequenceManager::createItem()
{
    return new LTXSequence();
}
