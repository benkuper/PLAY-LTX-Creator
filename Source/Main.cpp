#include "Main.h"

String getAppVersion();

#include "Audio/AudioManager.h"

LTXPlayCreatorApplication::LTXPlayCreatorApplication() :
	OrganicApplication("LTX Play Creator", true, ImageCache::getFromMemory(BinaryData::icon_png, BinaryData::icon_pngSize))
{
}

LTXPlayCreatorApplication::~LTXPlayCreatorApplication()
{
}

void LTXPlayCreatorApplication::initialiseInternal(const String&)
{
	AppUpdater::getInstance()->setURLs("http://benjamin.kuperberg.fr/playltxcreator/releases/update.json", "http://benjamin.kuperberg.fr/playltxcreator/download/app/", "PlayLTXCreator");
	HelpBox::getInstance()->helpURL = URL("http://benjamin.kuperberg.fr/playltxcreator/help/");
	CrashDumpUploader::getInstance()->init("http://benjamin.kuperberg.fr/playltxcreator/support/crash_report.php", ImageCache::getFromMemory(BinaryData::crash_png, BinaryData::crash_pngSize));

	engine.reset(new LTXEngine());

	if (useWindow) mainComponent.reset(new MainComponent());
	ShapeShifterManager::getInstance()->setLayoutInformations("ltxlayout", ProjectInfo::projectName + String("/layouts"));


	OSCRemoteControl::getInstance()->localPort->defaultValue = 27000;
	OSCRemoteControl::getInstance()->localPort->resetValue();

	GlobalSettings::getInstance()->addChildControllableContainer(AudioManager::getInstance());
}

bool LTXPlayCreatorApplication::moreThanOneInstanceAllowed()
{
	return false;
}
