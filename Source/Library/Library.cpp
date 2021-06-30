/*
  ==============================================================================

    Library.cpp
    Created: 30 Jun 2021 1:59:28pm
    Author:  bkupe

  ==============================================================================
*/

#include "Library.h"
#include "ColorPattern.h"
#include "PicturePattern.h"

juce_ImplementSingleton(Library)

Library::Library() :
    BaseManager("Library")
{
    gridThumbSize = addIntParameter("Thumb Size", "Size of thumbnails in grid view", 64, 32, 128);

    factory.defs.add(Factory<Pattern>::Definition::createDef<ColorPattern>("", "Color"));
    factory.defs.add(Factory<Pattern>::Definition::createDef<PicturePattern>("", "Picture"));

    managerFactory = &factory;
}

Library::~Library()
{
}
