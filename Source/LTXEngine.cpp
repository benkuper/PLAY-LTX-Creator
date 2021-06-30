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
	return data;
}

void LTXEngine::loadJSONDataInternalEngine(var data, ProgressTask* loadingTask)
{
	data.getDynamicObject()->setProperty(Library::getInstance()->shortName, Library::getInstance()->getJSONData());
}

String LTXEngine::getMinimumRequiredFileVersion()
{
	return "1.0.0b1";
}
