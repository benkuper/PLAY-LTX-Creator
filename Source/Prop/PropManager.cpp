/*
  ==============================================================================

    PropManager.cpp
    Created: 30 Jun 2021 1:57:35pm
    Author:  bkupe

  ==============================================================================
*/

#include "PropManager.h"

juce_ImplementSingleton(PropManager)

PropManager::PropManager() :
    BaseManager("Props")
{
}

PropManager::~PropManager()
{
}
