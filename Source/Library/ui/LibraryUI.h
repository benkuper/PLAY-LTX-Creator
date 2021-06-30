/*
  ==============================================================================

    LibraryUI.h
    Created: 30 Jun 2021 2:00:10pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once
#include "../Library.h"
#include "PatternUI.h"

class LibraryUI :
    public BaseManagerShapeShifterUI<Library, Pattern, PatternUI>,
    public ContainerAsyncListener
{
public:
    LibraryUI();
    ~LibraryUI();

    std::unique_ptr<IntSliderUI> thumbSizeUI;


    void resizedInternalHeader(Rectangle<int>& r) override;
    void resizedInternalContent(Rectangle<int>& r) override;
    
    PatternUI* createUIForItem(Pattern* item) override;

    void showMenuAndAddItem(bool, Point<int>) override;

    void newMessage(const ContainerAsyncEvent& e) override;
    int getDropIndexForPosition(Point<int> localPosition) override;

    static LibraryUI* create(const String& name) { return new LibraryUI(); }
};