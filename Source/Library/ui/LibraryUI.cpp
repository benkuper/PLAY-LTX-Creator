/*
  ==============================================================================

    LibraryUI.cpp
    Created: 30 Jun 2021 2:00:10pm
    Author:  bkupe

  ==============================================================================
*/

#include "LibraryUI.h"
#include "../PicturePattern.h"

LibraryUI::LibraryUI() :
    BaseManagerShapeShifterUI("Library", Library::getInstance())
{
    thumbSizeUI.reset(manager->gridThumbSize->createSlider());
    addAndMakeVisible(thumbSizeUI.get());
    thumbSizeUI->useCustomBGColor = true;
    thumbSizeUI->customBGColor = BG_COLOR.darker(.2f);
 
    manager->addAsyncCoalescedContainerListener(this);

    addExistingItems();
}

LibraryUI::~LibraryUI()
{
	manager->removeAsyncContainerListener(this);
}

void LibraryUI::resizedInternalHeader(Rectangle<int>& r)
{
    BaseManagerShapeShifterUI::resizedInternalHeader(r);
    r.removeFromLeft(4);
    thumbSizeUI->setBounds(r.removeFromLeft(150).reduced(3));
}

void LibraryUI::resizedInternalContent(Rectangle<int>& r)
{
	viewport.setBounds(r);

	const int thumbSize = manager->gridThumbSize->floatValue();

	int numThumbs = getFilteredItems().size();
	int numThumbPerLine = jmin(r.getWidth() / (thumbSize + gap), numThumbs);
	int numLines = numThumbs == 0 ? 0 : ceil(numThumbs * 1.f / numThumbPerLine);

	Rectangle<int> cr;
	cr.setSize(r.getWidth(), numLines * (thumbSize + gap) - gap);
	container.setSize(cr.getWidth(), cr.getHeight());

	int index = 0;
	int yIndex = 0;

	Rectangle<int> lr;

	for (auto& mui : itemsUI)
	{
		if (!checkFilterForItem(mui))
		{
			mui->setVisible(false);
			continue;
		}

		if (index % numThumbPerLine == 0)
		{
			int numThumbsInThisLine = jmin(numThumbs - index, numThumbPerLine);
			int lineWidth = numThumbsInThisLine * (thumbSize + gap) - gap;

			if (yIndex > 0) cr.removeFromTop(gap);
			lr = cr.removeFromTop(thumbSize);
			lr = lr.withSizeKeepingCentre(lineWidth, lr.getHeight());

			yIndex++;
		}

		mui->setBounds(lr.removeFromLeft(thumbSize));
		lr.removeFromLeft(gap);
		index++;
	}
}

PatternUI* LibraryUI::createUIForItem(Pattern* item)
{
	return item->createUI();
}


void LibraryUI::showMenuAndAddItem(bool, Point<int>)
{
	PopupMenu m = manager->factory.getMenu();
	m.addSeparator();
	m.addItem(-1, "Import Pictures...");

	if (int result = m.show())
	{
		switch (result)
		{
		case -1:
		{
			FileChooser fc("Import pictures", File::getSpecialLocation(File::userDocumentsDirectory), "*.jpg,*.jpeg,*.png,*.tiff,*.bpm");
			if (fc.browseForMultipleFilesToOpen())
			{
				Array<File> files = fc.getResults();
				Array<Pattern*> patterns;
				for (auto& f : files)
				{
					PicturePattern * pui = new PicturePattern();
					pui->file->setValue(f.getFullPathName());
					patterns.add(pui);
				}
				manager->addItems(patterns);
			}
		}
		break;

		default:
			manager->addItem(manager->factory.createFromMenuResult(result));
			break;
		}
	}
}


void LibraryUI::newMessage(const ContainerAsyncEvent& e)
{
	switch (e.type)
	{
	case ContainerAsyncEvent::ControllableFeedbackUpdate:
		if (e.targetControllable == manager->gridThumbSize) resized();
		break;

	default:
		break;
	}
}

int LibraryUI::getDropIndexForPosition(Point<int> localPosition)
{
	PatternUI * closestUI = nullptr;;
	float minDist = INT32_MAX;;
	bool rightSide = false;

	for (int i = 0; i < itemsUI.size(); ++i)
	{
		PatternUI* iui = itemsUI[i];
		Point<int> p = getLocalArea(iui, iui->getLocalBounds()).getCentre();

		float dist = p.getDistanceFrom(localPosition);
		if (dist < minDist)
		{
			closestUI = iui;
			minDist = dist;
			rightSide = localPosition.x > p.x;
		}
	}


	int index = itemsUI.indexOf(closestUI);
	if (rightSide) index++;

	return index;
}
