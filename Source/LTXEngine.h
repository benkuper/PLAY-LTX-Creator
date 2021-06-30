/*
  ==============================================================================

    LTXEngine.h
    Created: 30 Jun 2021 2:01:44pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"

class LTXEngine :
	public Engine,
	public OSCRemoteControl::RemoteControlListener
{
public:
	LTXEngine();
	~LTXEngine();

	void clearInternal() override;

	var getJSONData() override;
	void loadJSONDataInternalEngine(var data, ProgressTask* loadingTask) override;
	//void afterLoadFileInternal() override;

	String getMinimumRequiredFileVersion() override;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LTXEngine)
};