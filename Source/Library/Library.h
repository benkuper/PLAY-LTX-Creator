/*
  ==============================================================================

    Library.h
    Created: 30 Jun 2021 1:59:28pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once
#include "Pattern.h"

class Library :
    public BaseManager<Pattern>
{
public:
    juce_DeclareSingleton(Library, true)

    Library();
    ~Library();
};