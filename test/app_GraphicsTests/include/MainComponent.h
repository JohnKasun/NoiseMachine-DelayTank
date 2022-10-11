#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <list>

#include "DelayTankLookAndFeel.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::Component, public juce::MouseListener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    void mouseDown(const juce::MouseEvent& event) override;

private:

    std::list<Spot> mSpots;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
