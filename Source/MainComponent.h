#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/


class MainComponent : public OrganicMainContentComponent
{
public:
	//==============================================================================
	MainComponent();
	~MainComponent();

	void init() override;


	static SequenceManagerUI* createSequenceManagerUI(const String& name);

	//void getAllCommands(Array<CommandID>& commands) override;
	//virtual void getCommandInfo(CommandID commandID, ApplicationCommandInfo& result) override;
	//virtual bool perform(const InvocationInfo& info) override;
	//StringArray getMenuBarNames() override;
	//virtual PopupMenu getMenuForIndex(int topLevelMenuIndex, const String& menuName) override;
	//void fillFileMenuInternal(PopupMenu& menu) override;
};