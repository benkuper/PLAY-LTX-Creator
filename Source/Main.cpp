#include "Main.h"

String getAppVersion();

LTXPlayCreatorApplication::LTXPlayCreatorApplication() :
	OrganicApplication("LTX Play Creator", true, ImageCache::getFromMemory(BinaryData::icon_png, BinaryData::icon_pngSize))
{
}

LTXPlayCreatorApplication::~LTXPlayCreatorApplication()
{
}

void LTXPlayCreatorApplication::initialiseInternal(const String&)
{
	AppUpdater::getInstance()->setURLs("http://benjamin.kuperberg.fr/ltxplaycreator/releases/update.json", "http://benjamin.kuperberg.fr/ltxplaycreator/download/", "LTXPlayCreator");
	HelpBox::getInstance()->helpURL = URL("http://benjamin.kuperberg.fr/ltxplaycreator/help/");
	CrashDumpUploader::getInstance()->init("http://benjamin.kuperberg.fr/ltxplaycreator/support/crash_report.php", ImageCache::getFromMemory(BinaryData::crash_png, BinaryData::crash_pngSize));

	engine.reset(new LTXEngine());

	if (useWindow) mainComponent.reset(new MainComponent());
	ShapeShifterManager::getInstance()->setLayoutInformations("ltxlayout", ProjectInfo::projectName + String("/layouts"));


	OSCRemoteControl::getInstance()->localPort->defaultValue = 27000;
	OSCRemoteControl::getInstance()->localPort->resetValue();
}

bool LTXPlayCreatorApplication::moreThanOneInstanceAllowed()
{
	return false;
}