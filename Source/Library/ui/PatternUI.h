/*
  ==============================================================================

    PatternUI.h
    Created: 30 Jun 2021 2:00:13pm
    Author:  bkupe

  ==============================================================================
*/

#pragma once
#include "../Pattern.h"

class ColorPattern;
class PicturePattern;

class PatternUI :
    public BaseItemMinimalUI<Pattern>
{
public:
    PatternUI(Pattern* p);
    virtual ~PatternUI();
};


//



class ColorPatternUI :
    public PatternUI
{
public:
    ColorPatternUI(ColorPattern* cp);
    ~ColorPatternUI() {}

    ColorPattern* cp;

    void paint(Graphics& g) override;

    void controllableFeedbackUpdateInternal(Controllable* c) override;
};

class PicturePatternUI :
    public PatternUI
{
public:
    PicturePatternUI(PicturePattern* pp);
    ~PicturePatternUI() {}

    PicturePattern* pp;
    Image img;

    void updatePattern();

    void paint(Graphics& g) override;
    void controllableFeedbackUpdateInternal(Controllable* c) override;
};

