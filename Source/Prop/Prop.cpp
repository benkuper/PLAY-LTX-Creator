/*
  ==============================================================================

    Prop.cpp
    Created: 30 Jun 2021 1:57:38pm
    Author:  bkupe

  ==============================================================================
*/

#include "Prop.h"

Prop::Prop(var params) :
    BaseItem(params.getProperty("name",getTypeString()))
{
}

Prop::~Prop()
{
}
