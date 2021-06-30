/*
  ==============================================================================

    PatternLayerTimeline.cpp
    Created: 30 Jun 2021 2:01:11pm
    Author:  bkupe

  ==============================================================================
*/

#include "PatternLayerTimeline.h"
#include "PatternClipUI.h"
#include "Library/ui/PatternUI.h"


PatternLayerTimeline::PatternLayerTimeline(PatternLayer* layer) :
    SequenceLayerTimeline(layer),
    patternLayer(layer),
    clipManagerUI(this)
{
    addAndMakeVisible(&clipManagerUI);
}

PatternLayerTimeline::~PatternLayerTimeline()
{
}

void PatternLayerTimeline::resized()
{
    clipManagerUI.setBounds(getLocalBounds());
}

void PatternLayerTimeline::updateContent()
{
    clipManagerUI.updateContent();
}

PatternClipManagerUI::PatternClipManagerUI(PatternLayerTimeline* timeline) :
    LayerBlockManagerUI(timeline, &timeline->patternLayer->clipManager)
{
    acceptedDropTypes.add("Pattern");
    addExistingItems();
}

PatternClipManagerUI::~PatternClipManagerUI()
{
}

void PatternClipManagerUI::paint(Graphics& g)
{
	LayerBlockManagerUI::paint(g);
	if (dropClipX >= 0)
	{
		g.fillAll(BLUE_COLOR.withAlpha(.3f));
		g.setColour(HIGHLIGHT_COLOR);
		g.drawLine(dropClipX, 0, dropClipX, getHeight(), 4);
	}
}
LayerBlockUI* PatternClipManagerUI::createUIForItem(LayerBlock* item)
{
	return new PatternClipUI((PatternClip*)item);
}


void PatternClipManagerUI::itemDragEnter(const SourceDetails& source)
{
	dropClipX = source.localPosition.x;
	repaint();
}

void PatternClipManagerUI::itemDragExit(const SourceDetails& source)
{
	dropClipX = -1;
	repaint();
}

void PatternClipManagerUI::itemDragMove(const SourceDetails& source)
{
	dropClipX = source.localPosition.x;
	repaint();
}

void PatternClipManagerUI::itemDropped(const SourceDetails& source)
{
	dropClipX = -1;

	PatternUI* patternUI = dynamic_cast<PatternUI*>(source.sourceComponent.get());
	PatternClip* clip = (PatternClip*)manager->addBlockAt(timeline->getTimeForX(source.localPosition.x));
	if (patternUI == nullptr || clip == nullptr) return;

	clip->patternTarget->setValueFromTarget(patternUI->item);
}

