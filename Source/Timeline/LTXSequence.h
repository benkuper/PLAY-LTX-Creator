/*
  ==============================================================================

    LTXSequence.h
    Created: 30 Jun 2021 2:25:42pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"


class LTXAudioLayer;

class AudioModule;
class MTCSender;
class MIDIDeviceParameter;

class LTXSequence :
	public Sequence
{
public:
	LTXSequence();
	virtual ~LTXSequence();

	Factory<SequenceLayer> layerFactory;

	//virtual void clearItem() override;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LTXSequence)
};


