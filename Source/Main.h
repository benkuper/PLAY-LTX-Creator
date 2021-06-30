/*
  ==============================================================================

    Main.h
    Created: 30 Jun 2021 2:03:15pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#pragma warning(disable:4244 4100 4305)

#include "MainComponent.h"
#include "LTXEngine.h"

//==============================================================================
class LTXPlayCreatorApplication : public OrganicApplication
{
public:
	//==============================================================================
	LTXPlayCreatorApplication();
	~LTXPlayCreatorApplication();

	//==============================================================================
	void initialiseInternal(const String& /*commandLine*/) override;

	bool moreThanOneInstanceAllowed() override;
};



//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(LTXPlayCreatorApplication)
