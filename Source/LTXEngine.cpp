/*
  ==============================================================================

    LTXEngine.cpp
    Created: 30 Jun 2021 2:01:44pm
    Author:  bkupe

  ==============================================================================
*/

#include "LTXEngine.h"
#include "Prop/PropManager.h"
#include "Library/Library.h"
#include "Timeline/LTXSequenceManager.h"
#include "Audio/AudioManager.h"

LTXEngine::LTXEngine() :
	Engine(ProjectInfo::projectName, ".ltx")
{
	//init here
	Engine::mainEngine = this;
	addChildControllableContainer(Library::getInstance());
	addChildControllableContainer(PropManager::getInstance());
	addChildControllableContainer(LTXSequenceManager::getInstance());

	convertURL = "http://benjamin.kuperberg/ltxplaycreator/releases/convert.php";
	//breakingChangesVersions.add("2.1.0b1");
}

LTXEngine::~LTXEngine()
{
	LTXSequenceManager::deleteInstance();
	Library::deleteInstance();
	PropManager::deleteInstance();
	AudioManager::deleteInstance();
}

void LTXEngine::clearInternal()
{
	//clear
	LTXSequenceManager::getInstance()->clear();
	Library::getInstance()->clear();
}


var LTXEngine::getJSONData()
{
	var data = Engine::getJSONData();
	data.getDynamicObject()->setProperty(Library::getInstance()->shortName, Library::getInstance()->getJSONData());
	data.getDynamicObject()->setProperty(LTXSequenceManager::getInstance()->shortName, LTXSequenceManager::getInstance()->getJSONData());
	return data;
}

void LTXEngine::loadJSONDataInternalEngine(var data, ProgressTask* loadingTask)
{
	Library::getInstance()->loadJSONData(data.getProperty(Library::getInstance()->shortName, var()));
	LTXSequenceManager::getInstance()->loadJSONData(data.getProperty(LTXSequenceManager::getInstance()->shortName, var()));
}

String LTXEngine::getMinimumRequiredFileVersion()
{
	return "1.0.0b1";
}
