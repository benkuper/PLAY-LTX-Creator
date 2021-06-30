#include "MainComponent.h"
#include "Library/ui/LibraryUI.h"
#include "Timeline/LTXSequenceManager.h"

//==============================================================================
MainComponent::MainComponent()
{

	//getCommandManager().registerAllCommandsForTarget(this);
}

MainComponent::~MainComponent()
{
}

void MainComponent::init()
{

	//ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition("Module Router", &ModuleRouterPanelView::create));
	//ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition("Modules", &ModuleManagerUI::create));

	//ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition("Custom Variables", &CVGroupManagerUI::create));
	//ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition("Morpher", &MorpherPanel::create));

	ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition("Library", &LibraryUI::create));
	ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition("Sequences", &createSequenceManagerUI));
	ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition("Sequence Editor", &TimeMachineView::create));

	//ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition("States", &StateManagerUI::create));
	//ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition("State Machine", &StateMachineView::create));

	//ShapeShifterFactory::getInstance()->defs.add(new ShapeShifterDefinition("Command Templates", &CommandTemplateManagerPanel::create));


	OrganicMainContentComponent::init();
}

SequenceManagerUI* MainComponent::createSequenceManagerUI(const String& name)
{
    return SequenceManagerUI::create(name, LTXSequenceManager::getInstance());
}
